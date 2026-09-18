#include <stdio.h>
#include <string.h>

struct Etudiant
{
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note1;
    float note2;
};

int main(void)
{
    struct Etudiant etudiants[5];
    FILE *fichier;
    int i;

    fichier = fopen("etudiant.txt", "w");
    if (fichier == NULL)
    {
        printf("Erreur: impossible d'ouvrir etudiant.txt.\n");
        return 1;
    }

    for (i = 0; i < 5; ++i)
    {
        printf("Entrez les details de l'etudiant %d :\n", i + 1);
        printf("Nom : ");
        scanf("%49s", etudiants[i].nom);
        printf("Prenom : ");
        scanf("%49s", etudiants[i].prenom);
        printf("Adresse : ");
        scanf(" %99[^\n]", etudiants[i].adresse);
        printf("Note 1 : ");
        scanf("%f", &etudiants[i].note1);
        printf("Note 2 : ");
        scanf("%f", &etudiants[i].note2);

        fprintf(fichier,
                "%s %s %s %.2f %.2f\n",
                etudiants[i].nom,
                etudiants[i].prenom,
                etudiants[i].adresse,
                etudiants[i].note1,
                etudiants[i].note2);
    }

    fclose(fichier);
    printf("Les details des etudiants ont ete enregistres dans le fichier etudiant.txt.\n");
    return 0;
}
