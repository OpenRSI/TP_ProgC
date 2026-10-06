#include "fichier.h"
#include <stdio.h>
#include <stdlib.h>

void lire_fichier(const char *nom_de_fichier)
{
    FILE *fichier = fopen(nom_de_fichier, "r");
    char ligne[512];

    if (fichier == NULL)
    {
        printf("Erreur: impossible d'ouvrir le fichier '%s'.\n", nom_de_fichier);
        return;
    }

    printf("Contenu du fichier %s :\n", nom_de_fichier);
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        printf("%s", ligne);
    }
    fclose(fichier);
}

void ecrire_dans_fichier(const char *nom_de_fichier, const char *message)
{
    FILE *fichier = fopen(nom_de_fichier, "a");

    if (fichier == NULL)
    {
        printf("Erreur: impossible d'ouvrir le fichier '%s' pour ecriture.\n", nom_de_fichier);
        return;
    }

    fprintf(fichier, "%s\n", message);
    fclose(fichier);
    printf("Le message a ete ecrit dans le fichier %s.\n", nom_de_fichier);
}
