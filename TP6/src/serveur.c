/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include "protocole.h"
#include "serveur.h"

#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <netinet/in.h>
#include <signal.h>
#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char *svg_file_path = "pie_chart.svg";
static int socketfd = -1;
extern char **environ;

static int envoyer_tout(int client_socket_fd, const char *donnees,
                        size_t taille)
{
  size_t envoye = 0;
  while (envoye < taille)
  {
    ssize_t resultat = send(client_socket_fd, donnees + envoye,
                            taille - envoye, MSG_NOSIGNAL);
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

static int recevoir_ligne(int client_socket_fd, char *donnees, size_t capacite)
{
  size_t longueur = 0;
  while (longueur + 1 < capacite)
  {
    char caractere;
    ssize_t resultat = recv(client_socket_fd, &caractere, 1, 0);
    if (resultat < 0 && errno == EINTR)
      continue;
    if (resultat < 0)
    {
      perror("Erreur de reception");
      return -1;
    }
    if (resultat == 0)
      return longueur == 0 ? 0 : -1;
    donnees[longueur++] = caractere;
    if (caractere == '\n')
    {
      donnees[longueur] = '\0';
      return 1;
    }
  }
  return -1;
}

static int envoyer_json(int client_socket_fd, const char *code,
                        const char *valeur)
{
  char reponse[PROTOCOLE_TAILLE_MESSAGE];
  const char *valeurs[1] = {valeur};
  if (protocole_encoder(reponse, sizeof(reponse), code, 0, 0, valeurs, 1) != 0)
  {
    fprintf(stderr, "Impossible de creer la reponse JSON.\n");
    return -1;
  }
  return envoyer_tout(client_socket_fd, reponse, strlen(reponse));
}

static int couleur_valide(const char *couleur)
{
  if (strlen(couleur) != 7 || couleur[0] != '#')
    return 0;
  for (size_t i = 1; i < 7; ++i)
    if (!((couleur[i] >= '0' && couleur[i] <= '9') ||
          (couleur[i] >= 'a' && couleur[i] <= 'f') ||
          (couleur[i] >= 'A' && couleur[i] <= 'F')))
      return 0;
  return 1;
}

static int creer_graphique(const message_json *requete)
{
  FILE *fichier;
  const size_t nombre = requete->nombre_valeurs;
  const double centre_x = 200.0, centre_y = 200.0, rayon = 150.0;
  double angle_depart = -90.0;

  if (nombre == 0 || nombre > PROTOCOLE_MAX_VALEURS ||
      (requete->a_nombre && (requete->nombre < 1 || requete->nombre > 30 ||
                             (size_t)requete->nombre != nombre)))
    return -1;
  for (size_t i = 0; i < nombre; ++i)
    if (!couleur_valide(requete->valeurs[i]))
      return -1;

  fichier = fopen(svg_file_path, "w");
  if (fichier == NULL)
  {
    perror("Ouverture du fichier SVG");
    return -1;
  }

  fprintf(fichier, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(fichier, "<svg width=\"400\" height=\"400\" viewBox=\"0 0 400 400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(fichier, "  <rect width=\"400\" height=\"400\" fill=\"#ffffff\"/>\n");
  if (nombre == 1)
    fprintf(fichier, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" fill=\"%s\"/>\n",
            centre_x, centre_y, rayon, requete->valeurs[0]);
  else
  {
    for (size_t i = 0; i < nombre; ++i)
    {
      double angle_fin = i + 1 == nombre ? 270.0
                                         : angle_depart + 360.0 / nombre;
      double x1 = centre_x + rayon * cos(angle_depart * M_PI / 180.0);
      double y1 = centre_y + rayon * sin(angle_depart * M_PI / 180.0);
      double x2 = centre_x + rayon * cos(angle_fin * M_PI / 180.0);
      double y2 = centre_y + rayon * sin(angle_fin * M_PI / 180.0);
      int grand_arc = angle_fin - angle_depart > 180.0;

      fprintf(fichier,
              "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 %d,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\"/>\n",
              x1, y1, rayon, rayon, grand_arc, x2, y2, centre_x, centre_y,
              requete->valeurs[i]);
      angle_depart = angle_fin;
    }
  }
  fprintf(fichier, "</svg>\n");
  if (fclose(fichier) != 0)
  {
    perror("Ecriture du fichier SVG");
    return -1;
  }
  return 0;
}

static void ouvrir_dans_firefox(void)
{
  pid_t pid;
  char *const arguments[] = {"firefox", (char *)svg_file_path, NULL};
  int resultat = posix_spawnp(&pid, "firefox", NULL, NULL, arguments, environ);
  if (resultat != 0)
    fprintf(stderr, "Graphique cree dans %s; Firefox indisponible: %s\n",
            svg_file_path, strerror(resultat));
  else
    printf("Graphique cree dans %s et ouvert dans Firefox.\n", svg_file_path);
}

static int calculer(const message_json *requete, char *resultat,
                    size_t capacite)
{
  char *fin_a, *fin_b;
  long long a, b, valeur;
  char operateur;

  if (requete->nombre_valeurs != 3 || strlen(requete->valeurs[0]) != 1)
    return -1;
  operateur = requete->valeurs[0][0];
  errno = 0;
  a = strtoll(requete->valeurs[1], &fin_a, 10);
  if (errno != 0 || *requete->valeurs[1] == '\0' || *fin_a != '\0')
    return -1;
  errno = 0;
  b = strtoll(requete->valeurs[2], &fin_b, 10);
  if (errno != 0 || *requete->valeurs[2] == '\0' || *fin_b != '\0')
    return -1;

  switch (operateur)
  {
  case '+':
    if (__builtin_add_overflow(a, b, &valeur))
      return -1;
    break;
  case '-':
    if (__builtin_sub_overflow(a, b, &valeur))
      return -1;
    break;
  case '*':
    if (__builtin_mul_overflow(a, b, &valeur))
      return -1;
    break;
  case '/':
    if (b == 0 || (a == LLONG_MIN && b == -1))
      return -1;
    valeur = a / b;
    break;
  case '%':
    if (b == 0 || (a == LLONG_MIN && b == -1))
      return -1;
    valeur = a % b;
    break;
  default:
    return -1;
  }
  int taille = snprintf(resultat, capacite, "%lld", valeur);
  return taille >= 0 && (size_t)taille < capacite ? 0 : -1;
}

static int traiter_requete(int client_socket_fd, const char *donnees)
{
  message_json requete;
  char valeur[PROTOCOLE_TAILLE_VALEUR];

  if (protocole_decoder(donnees, &requete) != 0)
    return envoyer_json(client_socket_fd, "erreur", "Message JSON invalide.");

  if (strcmp(requete.code, "message") == 0)
  {
    if (requete.nombre_valeurs != 1)
      return envoyer_json(client_socket_fd, "erreur", "Message invalide.");
    return envoyer_json(client_socket_fd, "ok", requete.valeurs[0]);
  }
  if (strcmp(requete.code, "calcule") == 0)
  {
    if (calculer(&requete, valeur, sizeof(valeur)) != 0)
      return envoyer_json(client_socket_fd, "erreur", "Calcul invalide ou impossible.");
    return envoyer_json(client_socket_fd, "ok", valeur);
  }
  if (strcmp(requete.code, "couleurs") == 0)
  {
    if (creer_graphique(&requete) != 0)
      return envoyer_json(client_socket_fd, "erreur", "Liste de couleurs invalide.");
    ouvrir_dans_firefox();
    snprintf(valeur, sizeof(valeur), "Graphique genere: %s", svg_file_path);
    return envoyer_json(client_socket_fd, "ok", valeur);
  }
  return envoyer_json(client_socket_fd, "erreur", "Code d'operation inconnu.");
}

static void gestionnaire_ctrl_c(int signal_recu)
{
  (void)signal_recu;
  if (socketfd >= 0)
    close(socketfd);
  _exit(EXIT_SUCCESS);
}

int main(void)
{
  struct sockaddr_in adresse_serveur;
  int option = 1;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    return EXIT_FAILURE;
  }
  if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option,
                 sizeof(option)) != 0)
  {
    perror("setsockopt");
    close(socketfd);
    return EXIT_FAILURE;
  }

  memset(&adresse_serveur, 0, sizeof(adresse_serveur));
  adresse_serveur.sin_family = AF_INET;
  adresse_serveur.sin_port = htons(PORT);
  adresse_serveur.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socketfd, (struct sockaddr *)&adresse_serveur,
           sizeof(adresse_serveur)) != 0)
  {
    perror("bind");
    close(socketfd);
    return EXIT_FAILURE;
  }
  if (listen(socketfd, 10) != 0)
  {
    perror("listen");
    close(socketfd);
    return EXIT_FAILURE;
  }

  signal(SIGINT, gestionnaire_ctrl_c);
  signal(SIGCHLD, SIG_IGN);
  printf("Serveur en attente sur le port %d...\n", PORT);

  while (1)
  {
    struct sockaddr_in adresse_client;
    socklen_t taille_adresse = sizeof(adresse_client);
    int client_socket_fd = accept(socketfd,
                                  (struct sockaddr *)&adresse_client,
                                  &taille_adresse);
    if (client_socket_fd < 0)
    {
      if (errno == EINTR)
        continue;
      perror("accept");
      continue;
    }

    char donnees[PROTOCOLE_TAILLE_MESSAGE];
    int reception = recevoir_ligne(client_socket_fd, donnees, sizeof(donnees));
    if (reception == 1)
      traiter_requete(client_socket_fd, donnees);
    else
      envoyer_json(client_socket_fd, "erreur", "Requete incomplete ou trop longue.");
    close(client_socket_fd);
  }
}
