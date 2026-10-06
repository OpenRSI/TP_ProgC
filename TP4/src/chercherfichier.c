#include <stdio.h>
#include <string.h>

int main(void)
{
    char nom_fichier[128];
    char phrase[256];
    char ligne[512];
    FILE *fichier;
    int numero_ligne = 0;
    int trouve = 0;

    printf("Entrez le nom du fichier : ");
    scanf("%127s", nom_fichier);
    printf("Entrez la phrase a rechercher : ");
    scanf(" %255[^\n]", phrase);

    fichier = fopen(nom_fichier, "r");
    if (fichier == NULL)
    {
        printf("Erreur: impossible d'ouvrir le fichier.\n");
        return 1;
    }

    printf("Resultats de la recherche :\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        int occurrences = 0;
        char *ptr = ligne;
        ++numero_ligne;

        while ((ptr = strstr(ptr, phrase)) != NULL)
        {
            ++occurrences;
            ptr += strlen(phrase);
        }

        if (occurrences > 0)
        {
            printf("Ligne %d, %d fois\n", numero_ligne, occurrences);
            trouve = 1;
        }
    }

    fclose(fichier);

    if (!trouve)
    {
        printf("Aucune occurrence trouvee.\n");
    }

    return 0;
}
