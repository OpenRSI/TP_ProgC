#include "serveur.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static int socketfd = -1;

int renvoie_message(int client_socket_fd, char *data)
{
    int data_size = write(client_socket_fd, data, strlen(data));
    if (data_size < 0)
    {
        perror("Erreur d'écriture");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int recois_numeros_calcule(int client_socket_fd, char *data)
{
    char operateur;
    int num1, num2;
    int resultat;
    char reponse[256];

    if (sscanf(data, "calcule: %c %d %d", &operateur, &num1, &num2) != 3)
    {
        snprintf(reponse, sizeof(reponse), "Erreur: format invalide");
        return renvoie_message(client_socket_fd, reponse);
    }

    switch (operateur)
    {
        case '+':
            resultat = num1 + num2;
            break;
        case '-':
            resultat = num1 - num2;
            break;
        case '*':
            resultat = num1 * num2;
            break;
        case '/':
            if (num2 == 0)
            {
                snprintf(reponse, sizeof(reponse), "Erreur: division par zero");
                return renvoie_message(client_socket_fd, reponse);
            }
            resultat = num1 / num2;
            break;
        case '%':
            if (num2 == 0)
            {
                snprintf(reponse, sizeof(reponse), "Erreur: modulo par zero");
                return renvoie_message(client_socket_fd, reponse);
            }
            resultat = num1 % num2;
            break;
        case '&':
            resultat = num1 & num2;
            break;
        case '|':
            resultat = num1 | num2;
            break;
        default:
            snprintf(reponse, sizeof(reponse), "Erreur: operateur inconnu");
            return renvoie_message(client_socket_fd, reponse);
    }

    snprintf(reponse, sizeof(reponse), "%d", resultat);
    return renvoie_message(client_socket_fd, reponse);
}

int recois_envoie_message(int client_socket_fd, char *data)
{
    char code[32];

    printf("Message reçu: %s\n", data);

    if (sscanf(data, "%31[^:]:", code) == 1)
    {
        if (strcmp(code, "message") == 0)
        {
            return renvoie_message(client_socket_fd, data);
        }
        if (strcmp(code, "calcule") == 0)
        {
            return recois_numeros_calcule(client_socket_fd, data);
        }
    }

    return EXIT_SUCCESS;
}

void gestionnaire_ctrl_c(int signal)
{
    (void)signal;
    printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");
    if (socketfd != -1)
    {
        close(socketfd);
    }
    exit(0);
}

void gerer_client(int client_socket_fd)
{
    char data[1024];

    while (1)
    {
        memset(data, 0, sizeof(data));
        int data_size = read(client_socket_fd, data, sizeof(data));
        if (data_size <= 0)
        {
            if (data_size == 0)
            {
                printf("Client déconnecté.\n");
            }
            else
            {
                perror("Erreur de réception");
            }
            close(client_socket_fd);
            break;
        }

        recois_envoie_message(client_socket_fd, data);
    }
}

int main(void)
{
    int bind_status;
    struct sockaddr_in server_addr;
    int option = 1;
    int client_socket_fd;
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Impossible d'ouvrir une socket");
        return EXIT_FAILURE;
    }

    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_status < 0)
    {
        perror("bind");
        close(socketfd);
        return EXIT_FAILURE;
    }

    signal(SIGINT, gestionnaire_ctrl_c);
    listen(socketfd, 10);

    printf("Serveur en attente de connexions...\n");

    while (1)
    {
        client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket_fd < 0)
        {
            perror("accept");
            continue;
        }

        pid_t child_pid = fork();
        if (child_pid == 0)
        {
            close(socketfd);
            gerer_client(client_socket_fd);
            exit(0);
        }
        else if (child_pid < 0)
        {
            perror("fork");
            close(client_socket_fd);
        }
        else
        {
            close(client_socket_fd);
        }
    }

    return 0;
}
