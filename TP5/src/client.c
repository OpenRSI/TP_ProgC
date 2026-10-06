#include "client.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int envoie_recois_message(int socketfd)
{
    char message[1024];
    char data[2048];
    int write_status;
    int read_status;

    printf("Votre message (max 1000 caractères): ");
    if (fgets(message, sizeof(message), stdin) == NULL)
    {
        return -1;
    }

    message[strcspn(message, "\n")] = '\0';
    snprintf(data, sizeof(data), "message: %s", message);

    write_status = write(socketfd, data, strlen(data));
    if (write_status < 0)
    {
        perror("Erreur d'écriture");
        return -1;
    }

    memset(data, 0, sizeof(data));
    read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
        perror("Erreur de lecture");
        return -1;
    }

    printf("Message reçu: %s\n", data);
    return 0;
}

int envoie_operateur_numeros(int socketfd, char operateur, int num1, int num2)
{
    char data[2048];
    char reponse[2048];
    int write_status;
    int read_status;

    snprintf(data, sizeof(data), "calcule: %c %d %d", operateur, num1, num2);
    write_status = write(socketfd, data, strlen(data));
    if (write_status < 0)
    {
        perror("Erreur d'écriture");
        return -1;
    }

    memset(reponse, 0, sizeof(reponse));
    read_status = read(socketfd, reponse, sizeof(reponse));
    if (read_status < 0)
    {
        perror("Erreur de lecture");
        return -1;
    }

    printf("Resultat: %s\n", reponse);
    return 0;
}

int main(void)
{
    int socketfd;
    struct sockaddr_in server_addr;
    int choix;
    char operateur;
    int num1;
    int num2;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connection serveur");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("1. Envoyer un message\n2. Calculer\n0. Quitter\nVotre choix : ");
        if (scanf("%d", &choix) != 1)
        {
            break;
        }
        getchar();

        if (choix == 1)
        {
            envoie_recois_message(socketfd);
        }
        else if (choix == 2)
        {
            printf("Operateur (+, -, *, /, %%, &) : ");
            scanf(" %c", &operateur);
            printf("Nombre 1 : ");
            scanf("%d", &num1);
            printf("Nombre 2 : ");
            scanf("%d", &num2);
            envoie_operateur_numeros(socketfd, operateur, num1, num2);
        }
        else if (choix == 0)
        {
            break;
        }
    }

    close(socketfd);
    return 0;
}
