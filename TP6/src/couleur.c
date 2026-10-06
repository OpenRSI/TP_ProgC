/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "couleur.h"

#include <stdio.h>
#include <stdlib.h>

static int compare24(const void *gauche, const void *droite)
{
  const couleur24 *a = gauche;
  const couleur24 *b = droite;

  if (a->rouge != b->rouge)
    return (int)a->rouge - (int)b->rouge;
  if (a->vert != b->vert)
    return (int)a->vert - (int)b->vert;
  return (int)a->bleu - (int)b->bleu;
}

static int compare32(const void *gauche, const void *droite)
{
  const couleur32 *a = gauche;
  const couleur32 *b = droite;

  if (a->rouge != b->rouge)
    return (int)a->rouge - (int)b->rouge;
  if (a->vert != b->vert)
    return (int)a->vert - (int)b->vert;
  if (a->bleu != b->bleu)
    return (int)a->bleu - (int)b->bleu;
  return (int)a->alpha - (int)b->alpha;
}

static int compare_compte24(const void *gauche, const void *droite)
{
  const couleur24_compteur *a = gauche;
  const couleur24_compteur *b = droite;
  if (a->compte != b->compte)
    return a->compte < b->compte ? 1 : -1;
  return compare24(&a->c, &b->c);
}

static int compare_compte32(const void *gauche, const void *droite)
{
  const couleur32_compteur *a = gauche;
  const couleur32_compteur *b = droite;
  if (a->compte != b->compte)
    return a->compte < b->compte ? 1 : -1;
  return compare32(&a->c, &b->c);
}

couleur_compteur *compte_couleur(couleur *pixels, int taille)
{
  couleur_compteur *resultat;
  int uniques = 0;

  if (pixels == NULL || taille < 0 ||
      (pixels->compte_bit != BITS24 && pixels->compte_bit != BITS32))
    return NULL;

  resultat = calloc(1, sizeof(*resultat));
  if (resultat == NULL)
  {
    perror("calloc");
    return NULL;
  }
  resultat->compte_bit = pixels->compte_bit;

  if (pixels->compte_bit == BITS24)
  {
    qsort(pixels->c.c24, (size_t)taille, sizeof(couleur24), compare24);
    resultat->cc.cc24 = calloc((size_t)taille, sizeof(couleur24_compteur));
    if (taille != 0 && resultat->cc.cc24 == NULL)
      goto erreur;

    for (int i = 0; i < taille; ++i)
    {
      if (i == 0 || compare24(&pixels->c.c24[i - 1], &pixels->c.c24[i]) != 0)
      {
        resultat->cc.cc24[uniques].c = pixels->c.c24[i];
        resultat->cc.cc24[uniques].compte = 1;
        ++uniques;
      }
      else
        ++resultat->cc.cc24[uniques - 1].compte;
    }
    qsort(resultat->cc.cc24, (size_t)uniques,
          sizeof(couleur24_compteur), compare_compte24);
  }
  else
  {
    qsort(pixels->c.c32, (size_t)taille, sizeof(couleur32), compare32);
    resultat->cc.cc32 = calloc((size_t)taille, sizeof(couleur32_compteur));
    if (taille != 0 && resultat->cc.cc32 == NULL)
      goto erreur;

    for (int i = 0; i < taille; ++i)
    {
      if (i == 0 || compare32(&pixels->c.c32[i - 1], &pixels->c.c32[i]) != 0)
      {
        resultat->cc.cc32[uniques].c = pixels->c.c32[i];
        resultat->cc.cc32[uniques].compte = 1;
        ++uniques;
      }
      else
        ++resultat->cc.cc32[uniques - 1].compte;
    }
    qsort(resultat->cc.cc32, (size_t)uniques,
          sizeof(couleur32_compteur), compare_compte32);
  }

  resultat->size = uniques;
  return resultat;

erreur:
  perror("calloc");
  free(resultat);
  return NULL;
}

void print_couleur(couleur *pixels, int taille)
{
  if (pixels == NULL)
    return;

  for (int i = 0; i < taille; ++i)
  {
    if (pixels->compte_bit == BITS24)
      printf("%02x %02x %02x\n", pixels->c.c24[i].rouge,
             pixels->c.c24[i].vert, pixels->c.c24[i].bleu);
    else if (pixels->compte_bit == BITS32)
      printf("%02x %02x %02x %02x\n", pixels->c.c32[i].rouge,
             pixels->c.c32[i].vert, pixels->c.c32[i].bleu,
             pixels->c.c32[i].alpha);
  }
}

void print_couleur_compteur(couleur_compteur *compteur)
{
  if (compteur == NULL)
    return;

  for (int i = 0; i < compteur->size; ++i)
  {
    if (compteur->compte_bit == BITS24)
      printf("%02x %02x %02x: %d\n",
             compteur->cc.cc24[i].c.rouge,
             compteur->cc.cc24[i].c.vert,
             compteur->cc.cc24[i].c.bleu,
             compteur->cc.cc24[i].compte);
    else if (compteur->compte_bit == BITS32)
      printf("%02x %02x %02x %02x: %d\n",
             compteur->cc.cc32[i].c.rouge,
             compteur->cc.cc32[i].c.vert,
             compteur->cc.cc32[i].c.bleu,
             compteur->cc.cc32[i].c.alpha,
             compteur->cc.cc32[i].compte);
  }
}

void trier_couleur_compteur(couleur_compteur *compteur)
{
  if (compteur == NULL)
    return;
  if (compteur->compte_bit == BITS24)
    qsort(compteur->cc.cc24, (size_t)compteur->size,
          sizeof(couleur24_compteur), compare_compte24);
  else if (compteur->compte_bit == BITS32)
    qsort(compteur->cc.cc32, (size_t)compteur->size,
          sizeof(couleur32_compteur), compare_compte32);
}
