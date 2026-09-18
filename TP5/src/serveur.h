#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

int renvoie_message(int client_socket_fd, char *data);
int recois_envoie_message(int client_socket_fd, char *data);
int recois_numeros_calcule(int client_socket_fd, char *data);

#endif
