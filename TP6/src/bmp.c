/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define _FILE_OFFSET_BITS 64
#define _POSIX_C_SOURCE 200809L
#include "bmp.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

couleur_compteur *analyse_bmp_image(const char *nom_de_fichier)
{
  FILE *fichier = fopen(nom_de_fichier, "rb");
  bmp_header entete;
  bmp_info_header info;
  couleur pixels;
  couleur_compteur *resultat = NULL;
  unsigned char *ligne = NULL;
  uint64_t largeur, hauteur, octets_ligne, taille_ligne, nombre_pixels;
  int hauteur_signee;

  if (fichier == NULL)
  {
    perror(nom_de_fichier);
    return NULL;
  }

  if (fread(&entete, sizeof(entete), 1, fichier) != 1 ||
      fread(&info, sizeof(info), 1, fichier) != 1)
  {
    fprintf(stderr, "Erreur: en-tete BMP incomplet.\n");
    goto nettoyage;
  }

  hauteur_signee = (int32_t)info.hauteur;
  if (entete.type != 0x4D42 || info.info_header_size < sizeof(info) ||
      info.largeur == 0 || hauteur_signee == 0 || info.planes != 1 ||
      (info.compte_bit != 24 && info.compte_bit != 32) ||
      info.compression != 0)
  {
    fprintf(stderr, "Erreur: BMP invalide ou format non pris en charge (24/32 bits non compresse requis).\n");
    goto nettoyage;
  }

  largeur = info.largeur;
  hauteur = hauteur_signee < 0 ? (uint64_t)(-(int64_t)hauteur_signee)
                               : (uint64_t)hauteur_signee;
  nombre_pixels = largeur * hauteur;
  if (nombre_pixels > INT_MAX ||
      largeur > (UINT64_MAX - 3) / (info.compte_bit / 8))
  {
    fprintf(stderr, "Erreur: image BMP trop grande.\n");
    goto nettoyage;
  }

  octets_ligne = largeur * (info.compte_bit / 8);
  taille_ligne = (octets_ligne + 3) & ~UINT64_C(3);
  if (taille_ligne > SIZE_MAX)
  {
    fprintf(stderr, "Erreur: ligne BMP trop grande.\n");
    goto nettoyage;
  }

  ligne = malloc((size_t)taille_ligne);
  if (ligne == NULL)
  {
    perror("malloc");
    goto nettoyage;
  }

  pixels.compte_bit = info.compte_bit == 24 ? BITS24 : BITS32;
  pixels.size = (int)nombre_pixels;
  if (pixels.compte_bit == BITS24)
  {
    if (nombre_pixels > SIZE_MAX / sizeof(couleur24))
      goto nettoyage;
    pixels.c.c24 = malloc((size_t)nombre_pixels * sizeof(couleur24));
  }
  else
  {
    if (nombre_pixels > SIZE_MAX / sizeof(couleur32))
      goto nettoyage;
    pixels.c.c32 = malloc((size_t)nombre_pixels * sizeof(couleur32));
  }

  if ((pixels.compte_bit == BITS24 && pixels.c.c24 == NULL) ||
      (pixels.compte_bit == BITS32 && pixels.c.c32 == NULL))
  {
    perror("malloc");
    goto nettoyage;
  }

  if (fseeko(fichier, (off_t)entete.offset, SEEK_SET) != 0)
  {
    perror("fseeko");
    goto liberation_pixels;
  }

  for (uint64_t y = 0; y < hauteur; ++y)
  {
    uint64_t destination_y = hauteur_signee < 0 ? y : hauteur - 1 - y;
    if (fread(ligne, 1, (size_t)taille_ligne, fichier) != taille_ligne)
    {
      fprintf(stderr, "Erreur: donnees BMP incompletes.\n");
      goto liberation_pixels;
    }

    for (uint64_t x = 0; x < largeur; ++x)
    {
      size_t index = (size_t)(destination_y * largeur + x);
      size_t source = (size_t)(x * (info.compte_bit / 8));
      if (pixels.compte_bit == BITS24)
      {
        pixels.c.c24[index].bleu = ligne[source];
        pixels.c.c24[index].vert = ligne[source + 1];
        pixels.c.c24[index].rouge = ligne[source + 2];
      }
      else
      {
        pixels.c.c32[index].bleu = ligne[source];
        pixels.c.c32[index].vert = ligne[source + 1];
        pixels.c.c32[index].rouge = ligne[source + 2];
        pixels.c.c32[index].alpha = 255;
      }
    }
  }

  resultat = compte_couleur(&pixels, pixels.size);

liberation_pixels:
  if (pixels.compte_bit == BITS24)
    free(pixels.c.c24);
  else
    free(pixels.c.c32);
nettoyage:
  free(ligne);
  fclose(fichier);
  return resultat;
}
