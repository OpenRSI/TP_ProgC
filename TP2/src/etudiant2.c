#include <stdio.h>
#include <string.h>

struct Etudiant
{
    char nom[50];
    char prenom[50];
    char adresse[100];
    float noteProg;
    float noteSys;
};

int main(void)
{
    int i;
    struct Etudiant etudiants[5] = {
        {"Dupont", "Marie", "20, Boulevard Niels Bohr, Lyon", 16.5f, 12.1f},
        {"Martin", "Pierre", "22, Boulevard Niels Bohr, Lyon", 14.0f, 14.1f},
        {"Bernard", "Claire", "10, Rue de la Republique, Paris", 12.5f, 11.8f},
        {"Lemoine", "Sophie", "15, Avenue des Champs, Marseille", 17.0f, 15.5f},
        {"Moreau", "Luc", "8, Rue du Lac, Grenoble", 13.8f, 12.9f}
    };

    for (i = 0; i < 5; ++i)
    {
        printf("Etudiant %d :\n", i + 1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prenom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Note 1 : %.1f\n", etudiants[i].noteProg);
        printf("Note 2 : %.1f\n\n", etudiants[i].noteSys);
    }

    return 0;
}
