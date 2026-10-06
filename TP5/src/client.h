#ifndef __CLIENT_H__
#define __CLIENT_H__

#define PORT 8089

int envoie_recois_message(int socketfd);
int envoie_operateur_numeros(int socketfd, char operateur, int num1, int num2);

#endif
