#ifndef TP6_PROTOCOLE_H
#define TP6_PROTOCOLE_H

#include <stddef.h>

#define PROTOCOLE_MAX_VALEURS 30
#define PROTOCOLE_TAILLE_VALEUR 1024
#define PROTOCOLE_TAILLE_MESSAGE 32768

typedef struct
{
  char code[32];
  int nombre;
  int a_nombre;
  size_t nombre_valeurs;
  char valeurs[PROTOCOLE_MAX_VALEURS][PROTOCOLE_TAILLE_VALEUR];
} message_json;

int protocole_encoder(char *, size_t, const char *, int, int,
                      const char *const *, size_t);
int protocole_decoder(const char *, message_json *);

#endif
