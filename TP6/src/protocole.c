#include "protocole.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  const char *texte;
  size_t position;
} lecteur_json;

static int ajouter(char *destination, size_t capacite, size_t *longueur,
                   const char *texte, size_t taille)
{
  if (taille >= capacite - *longueur)
    return -1;
  memcpy(destination + *longueur, texte, taille);
  *longueur += taille;
  destination[*longueur] = '\0';
  return 0;
}

static int encoder_chaine(char *destination, size_t capacite,
                          size_t *longueur, const char *texte)
{
  if (ajouter(destination, capacite, longueur, "\"", 1) != 0)
    return -1;

  for (const unsigned char *p = (const unsigned char *)texte; *p; ++p)
  {
    char echappe[7];
    const char *sortie = NULL;
    size_t taille = 0;
    switch (*p)
    {
    case '"':
      sortie = "\\\"";
      taille = 2;
      break;
    case '\\':
      sortie = "\\\\";
      taille = 2;
      break;
    case '\b':
      sortie = "\\b";
      taille = 2;
      break;
    case '\f':
      sortie = "\\f";
      taille = 2;
      break;
    case '\n':
      sortie = "\\n";
      taille = 2;
      break;
    case '\r':
      sortie = "\\r";
      taille = 2;
      break;
    case '\t':
      sortie = "\\t";
      taille = 2;
      break;
    default:
      if (*p < 0x20)
      {
        int ecrit = snprintf(echappe, sizeof(echappe), "\\u%04x", *p);
        if (ecrit != 6)
          return -1;
        sortie = echappe;
        taille = 6;
      }
      else
      {
        sortie = (const char *)p;
        taille = 1;
      }
      break;
    }
    if (ajouter(destination, capacite, longueur, sortie, taille) != 0)
      return -1;
  }
  return ajouter(destination, capacite, longueur, "\"", 1);
}

int protocole_encoder(char *destination, size_t capacite, const char *code,
                      int a_nombre, int nombre, const char *const *valeurs,
                      size_t nombre_valeurs)
{
  size_t longueur = 0;
  char nombre_texte[32];

  if (destination == NULL || capacite == 0 || code == NULL ||
      nombre_valeurs > PROTOCOLE_MAX_VALEURS ||
      (nombre_valeurs != 0 && valeurs == NULL))
    return -1;
  destination[0] = '\0';

  if (ajouter(destination, capacite, &longueur, "{\"code\":", 8) != 0 ||
      encoder_chaine(destination, capacite, &longueur, code) != 0)
    return -1;

  if (a_nombre)
  {
    int taille = snprintf(nombre_texte, sizeof(nombre_texte),
                          ",\"nombre\":%d", nombre);
    if (taille < 0 || (size_t)taille >= sizeof(nombre_texte) ||
        ajouter(destination, capacite, &longueur, nombre_texte,
                (size_t)taille) != 0)
      return -1;
  }

  if (ajouter(destination, capacite, &longueur, ",\"valeurs\":[", 12) != 0)
    return -1;
  for (size_t i = 0; i < nombre_valeurs; ++i)
  {
    if (valeurs[i] == NULL ||
        (i != 0 && ajouter(destination, capacite, &longueur, ",", 1) != 0) ||
        encoder_chaine(destination, capacite, &longueur, valeurs[i]) != 0)
      return -1;
  }

  return ajouter(destination, capacite, &longueur, "]}\n", 3);
}

static void espaces(lecteur_json *lecteur)
{
  while (isspace((unsigned char)lecteur->texte[lecteur->position]))
    ++lecteur->position;
}

static int caractere(lecteur_json *lecteur, char attendu)
{
  espaces(lecteur);
  if (lecteur->texte[lecteur->position] != attendu)
    return -1;
  ++lecteur->position;
  return 0;
}

static int caractere_exact(lecteur_json *lecteur, char attendu)
{
  if (lecteur->texte[lecteur->position] != attendu)
    return -1;
  ++lecteur->position;
  return 0;
}

static int hex_digit(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;
  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;
  return -1;
}

static int lire_hex4(lecteur_json *lecteur, unsigned int *resultat)
{
  unsigned int valeur = 0;
  for (int i = 0; i < 4; ++i)
  {
    if (lecteur->texte[lecteur->position] == '\0')
      return -1;
    int chiffre = hex_digit(lecteur->texte[lecteur->position++]);
    if (chiffre < 0)
      return -1;
    valeur = (valeur << 4) | (unsigned int)chiffre;
  }
  *resultat = valeur;
  return 0;
}

static int ajouter_utf8(char *sortie, size_t capacite, size_t *longueur,
                        unsigned int point)
{
  char octets[4];
  size_t taille;
  if (point == 0)
    return -1;
  if (point <= 0x7f)
  {
    octets[0] = (char)point;
    taille = 1;
  }
  else if (point <= 0x7ff)
  {
    octets[0] = (char)(0xc0 | (point >> 6));
    octets[1] = (char)(0x80 | (point & 0x3f));
    taille = 2;
  }
  else if (point <= 0xffff)
  {
    octets[0] = (char)(0xe0 | (point >> 12));
    octets[1] = (char)(0x80 | ((point >> 6) & 0x3f));
    octets[2] = (char)(0x80 | (point & 0x3f));
    taille = 3;
  }
  else if (point <= 0x10ffff)
  {
    octets[0] = (char)(0xf0 | (point >> 18));
    octets[1] = (char)(0x80 | ((point >> 12) & 0x3f));
    octets[2] = (char)(0x80 | ((point >> 6) & 0x3f));
    octets[3] = (char)(0x80 | (point & 0x3f));
    taille = 4;
  }
  else
    return -1;
  return ajouter(sortie, capacite, longueur, octets, taille);
}

static int lire_chaine(lecteur_json *lecteur, char *sortie, size_t capacite)
{
  size_t longueur = 0;
  if (caractere(lecteur, '"') != 0 || capacite == 0)
    return -1;
  sortie[0] = '\0';

  while (lecteur->texte[lecteur->position] != '\0')
  {
    unsigned char c = (unsigned char)lecteur->texte[lecteur->position++];
    if (c == '"')
      return 0;
    if (c < 0x20)
      return -1;
    if (c == '\\')
    {
      c = (unsigned char)lecteur->texte[lecteur->position++];
      switch (c)
      {
      case '"':
      case '\\':
      case '/':
        break;
      case 'b':
        c = '\b';
        break;
      case 'f':
        c = '\f';
        break;
      case 'n':
        c = '\n';
        break;
      case 'r':
        c = '\r';
        break;
      case 't':
        c = '\t';
        break;
      case 'u':
      {
        unsigned int point;
        if (lire_hex4(lecteur, &point) != 0)
          return -1;
        if (point >= 0xd800 && point <= 0xdbff)
        {
          unsigned int bas;
          if (caractere_exact(lecteur, '\\') != 0 ||
              caractere_exact(lecteur, 'u') != 0 ||
              lire_hex4(lecteur, &bas) != 0 || bas < 0xdc00 || bas > 0xdfff)
            return -1;
          point = 0x10000 + ((point - 0xd800) << 10) + (bas - 0xdc00);
        }
        else if (point >= 0xdc00 && point <= 0xdfff)
          return -1;
        if (ajouter_utf8(sortie, capacite, &longueur, point) != 0)
          return -1;
        continue;
      }
      default:
        return -1;
      }
    }
    if (ajouter(sortie, capacite, &longueur, (const char *)&c, 1) != 0)
      return -1;
  }
  return -1;
}

static int lire_nombre(lecteur_json *lecteur, int *nombre)
{
  char *fin;
  const char *debut;
  const char *chiffres;
  long valeur;
  espaces(lecteur);
  debut = lecteur->texte + lecteur->position;
  chiffres = debut + (*debut == '-' ? 1 : 0);
  if (*chiffres == '0')
  {
    ++chiffres;
    if (isdigit((unsigned char)*chiffres))
      return -1;
  }
  else
  {
    if (*chiffres < '1' || *chiffres > '9')
      return -1;
    while (isdigit((unsigned char)*chiffres))
      ++chiffres;
  }
  if (chiffres == debut || (debut[0] == '-' && chiffres == debut + 1))
    return -1;
  errno = 0;
  valeur = strtol(debut, &fin, 10);
  if (errno == ERANGE || fin == debut ||
      fin != chiffres ||
      valeur < -2147483647L - 1 || valeur > 2147483647L)
    return -1;
  if (*fin != ',' && *fin != '}' && !isspace((unsigned char)*fin))
    return -1;
  lecteur->position = (size_t)(fin - lecteur->texte);
  *nombre = (int)valeur;
  return 0;
}

static int lire_valeurs(lecteur_json *lecteur, message_json *message)
{
  if (caractere(lecteur, '[') != 0)
    return -1;
  espaces(lecteur);
  if (lecteur->texte[lecteur->position] == ']')
  {
    ++lecteur->position;
    return 0;
  }
  while (message->nombre_valeurs < PROTOCOLE_MAX_VALEURS)
  {
    if (lire_chaine(lecteur,
                    message->valeurs[message->nombre_valeurs],
                    sizeof(message->valeurs[0])) != 0)
      return -1;
    ++message->nombre_valeurs;
    espaces(lecteur);
    if (lecteur->texte[lecteur->position] == ']')
    {
      ++lecteur->position;
      return 0;
    }
    if (caractere(lecteur, ',') != 0)
      return -1;
  }
  return -1;
}

int protocole_decoder(const char *texte, message_json *message)
{
  lecteur_json lecteur = {texte, 0};
  int code_present = 0, valeurs_presentes = 0;

  if (texte == NULL || message == NULL)
    return -1;
  memset(message, 0, sizeof(*message));
  if (caractere(&lecteur, '{') != 0)
    return -1;

  espaces(&lecteur);
  while (lecteur.texte[lecteur.position] != '}')
  {
    char cle[32];
    if (lire_chaine(&lecteur, cle, sizeof(cle)) != 0 ||
        caractere(&lecteur, ':') != 0)
      return -1;

    if (strcmp(cle, "code") == 0 && !code_present)
    {
      if (lire_chaine(&lecteur, message->code, sizeof(message->code)) != 0)
        return -1;
      code_present = 1;
    }
    else if (strcmp(cle, "nombre") == 0 && !message->a_nombre)
    {
      if (lire_nombre(&lecteur, &message->nombre) != 0)
        return -1;
      message->a_nombre = 1;
    }
    else if (strcmp(cle, "valeurs") == 0 && !valeurs_presentes)
    {
      if (lire_valeurs(&lecteur, message) != 0)
        return -1;
      valeurs_presentes = 1;
    }
    else
      return -1;

    espaces(&lecteur);
    if (lecteur.texte[lecteur.position] == '}')
      break;
    if (caractere(&lecteur, ',') != 0)
      return -1;
  }

  if (caractere(&lecteur, '}') != 0 || !code_present || !valeurs_presentes)
    return -1;
  espaces(&lecteur);
  return lecteur.texte[lecteur.position] == '\0' ? 0 : -1;
}
