/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bmp.h"
#include "client.h"
#include "protocole.h"

#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static int envoyer_tout(int socketfd, const char *donnees, size_t taille)
{
  size_t envoye = 0;
  while (envoye < taille)
  {
    ssize_t resultat = send(socketfd, donnees + envoye, taille - envoye,
                            MSG_NOSIGNAL);
    if (resultat < 0 && errno == EINTR)
      continue;
    if (resultat <= 0)
    {
      perror("Erreur d'envoi");
      return -1;
    }
    envoye += (size_t)resultat;
  }
  return 0;
}

static int recevoir_ligne(int socketfd, char *donnees, size_t capacite)
{
  size_t longueur = 0;
  while (longueur + 1 < capacite)
  {
    char caractere;
    ssize_t resultat = recv(socketfd, &caractere, 1, 0);
    if (resultat < 0 && errno == EINTR)
      continue;
    if (resultat < 0)
    {
      perror("Erreur de reception");
      return -1;
    }
    if (resultat == 0)
    {
      fprintf(stderr, "Le serveur a ferme la connexion sans reponse complete.\n");
      return -1;
    }
    donnees[longueur++] = caractere;
    if (caractere == '\n')
    {
      donnees[longueur] = '\0';
      return 0;
    }
  }
  fprintf(stderr, "Reponse du serveur trop longue.\n");
  return -1;
}

static int echanger(int socketfd, const char *requete)
{
  char reponse[PROTOCOLE_TAILLE_MESSAGE];
  message_json message;
  size_t taille = strlen(requete);

  if (envoyer_tout(socketfd, requete, taille) != 0 ||
      recevoir_ligne(socketfd, reponse, sizeof(reponse)) != 0)
    return -1;

  if (protocole_decoder(reponse, &message) != 0)
  {
    fprintf(stderr, "Reponse JSON invalide recue du serveur.\n");
    return -1;
  }
  if (strcmp(message.code, "erreur") == 0)
  {
    fprintf(stderr, "Erreur du serveur: %s\n",
            message.nombre_valeurs ? message.valeurs[0] : "requete refusee");
    return -1;
  }
  for (size_t i = 0; i < message.nombre_valeurs; ++i)
    printf("%s\n", message.valeurs[i]);
  return 0;
}

static int lire_entier(const char *texte, int minimum, int maximum, int *valeur)
{
  char *fin;
  long resultat;
  errno = 0;
  resultat = strtol(texte, &fin, 10);
  if (errno != 0 || *texte == '\0' || *fin != '\0' ||
      resultat < minimum || resultat > maximum)
    return -1;
  *valeur = (int)resultat;
  return 0;
}

static void liberer_compteur(couleur_compteur *compteur)
{
  if (compteur == NULL)
    return;
  if (compteur->compte_bit == BITS24)
    free(compteur->cc.cc24);
  else
    free(compteur->cc.cc32);
  free(compteur);
}

static int envoyer_analyse(int socketfd, const char *chemin, int nombre)
{
  couleur_compteur *compteur = analyse_bmp_image(chemin);
  char couleurs[PROTOCOLE_MAX_VALEURS][8];
  const char *valeurs[PROTOCOLE_MAX_VALEURS];
  char requete[PROTOCOLE_TAILLE_MESSAGE];
  size_t taille_couleurs;

  if (compteur == NULL)
    return -1;

  taille_couleurs = (size_t)compteur->size;
  if (taille_couleurs > (size_t)nombre)
    taille_couleurs = (size_t)nombre;
  if (taille_couleurs == 0)
  {
    fprintf(stderr, "L'image ne contient aucune couleur.\n");
    liberer_compteur(compteur);
    return -1;
  }

  for (size_t i = 0; i < taille_couleurs; ++i)
  {
    int rouge, vert, bleu;
    if (compteur->compte_bit == BITS24)
    {
      rouge = compteur->cc.cc24[i].c.rouge;
      vert = compteur->cc.cc24[i].c.vert;
      bleu = compteur->cc.cc24[i].c.bleu;
    }
    else
    {
      rouge = compteur->cc.cc32[i].c.rouge;
      vert = compteur->cc.cc32[i].c.vert;
      bleu = compteur->cc.cc32[i].c.bleu;
    }
    snprintf(couleurs[i], sizeof(couleurs[i]), "#%02x%02x%02x",
             rouge, vert, bleu);
    valeurs[i] = couleurs[i];
  }

  if (protocole_encoder(requete, sizeof(requete), "couleurs", 1, (int)taille_couleurs,
                        valeurs, taille_couleurs) != 0)
  {
    fprintf(stderr, "Impossible de creer le message JSON des couleurs.\n");
    liberer_compteur(compteur);
    return -1;
  }

  printf("%zu couleur(s) dominante(s) envoyee(s).\n", taille_couleurs);
  liberer_compteur(compteur);
  return echanger(socketfd, requete);
}

static int connexion_serveur(void)
{
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in adresse;

  if (socketfd < 0)
  {
    perror("socket");
    return -1;
  }

  memset(&adresse, 0, sizeof(adresse));
  adresse.sin_family = AF_INET;
  adresse.sin_port = htons(PORT);
  if (inet_pton(AF_INET, "127.0.0.1", &adresse.sin_addr) != 1)
  {
    fprintf(stderr, "Adresse serveur invalide.\n");
    close(socketfd);
    return -1;
  }
  if (connect(socketfd, (struct sockaddr *)&adresse, sizeof(adresse)) != 0)
  {
    perror("Connexion au serveur");
    close(socketfd);
    return -1;
  }
  return socketfd;
}

static void afficher_usage(const char *programme)
{
  fprintf(stderr,
          "Usage:\n"
          "  %s image.bmp [nombre_de_couleurs (1-30)]\n"
          "  %s --message texte\n"
          "  %s --calculate operateur nombre1 nombre2\n",
          programme, programme, programme);
}

int main(int argc, char **argv)
{
  char requete[PROTOCOLE_TAILLE_MESSAGE];
  const char *valeurs[3];
  int nombre = 10;
  int socketfd;
  int statut;

  if (argc == 3 && strcmp(argv[1], "--message") == 0)
  {
    valeurs[0] = argv[2];
    statut = protocole_encoder(requete, sizeof(requete), "message", 0, 0,
                               valeurs, 1);
  }
  else if (argc == 5 && strcmp(argv[1], "--calculate") == 0)
  {
    int a, b;
    if (strlen(argv[2]) != 1 ||
        strchr("+-*/%", argv[2][0]) == NULL ||
        lire_entier(argv[3], INT_MIN, INT_MAX, &a) != 0 ||
        lire_entier(argv[4], INT_MIN, INT_MAX, &b) != 0)
    {
      afficher_usage(argv[0]);
      return EXIT_FAILURE;
    }
    valeurs[0] = argv[2];
    valeurs[1] = argv[3];
    valeurs[2] = argv[4];
    statut = protocole_encoder(requete, sizeof(requete), "calcule", 0, 0,
                               valeurs, 3);
  }
  else if ((argc == 2 || argc == 3) && argv[1][0] != '-')
  {
    if (argc == 3 && lire_entier(argv[2], 1, 30, &nombre) != 0)
    {
      fprintf(stderr, "Le nombre de couleurs doit etre compris entre 1 et 30.\n");
      return EXIT_FAILURE;
    }
    socketfd = connexion_serveur();
    if (socketfd < 0)
      return EXIT_FAILURE;
    statut = envoyer_analyse(socketfd, argv[1], nombre);
    close(socketfd);
    return statut == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  else
  {
    afficher_usage(argv[0]);
    return EXIT_FAILURE;
  }

  if (statut != 0)
  {
    fprintf(stderr, "Impossible de creer le message JSON.\n");
    return EXIT_FAILURE;
  }
  socketfd = connexion_serveur();
  if (socketfd < 0)
    return EXIT_FAILURE;
  statut = echanger(socketfd, requete);
  close(socketfd);
  return statut == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
