#include <stdio.h>

int main(void)
{
    int i;
    const int nombre = 5;
    char noms[5][50] = {
        "Dupont", "Martin", "Bernard", "Lemoine", "Moreau"
    };
    char prenoms[5][50] = {
        "Marie", "Pierre", "Claire", "Sophie", "Luc"
    };
    char adresses[5][100] = {
        "20, Boulevard Niels Bohr, Lyon",
        "22, Boulevard Niels Bohr, Lyon",
        "10, Rue de la Republique, Paris",
        "15, Avenue des Champs, Marseille",
        "8, Rue du Lac, Grenoble"
    };
    float notesC[5] = {16.5f, 14.0f, 12.5f, 17.0f, 13.8f};
    float notesSys[5] = {12.1f, 14.1f, 11.8f, 15.5f, 12.9f};

    for (i = 0; i < nombre; ++i)
    {
        printf("Etudiant %d\n", i + 1);
        printf("Nom : %s\n", noms[i]);
        printf("Prenom : %s\n", prenoms[i]);
        printf("Adresse : %s\n", adresses[i]);
        printf("Note C : %.1f\n", notesC[i]);
        printf("Note Systeme : %.1f\n\n", notesSys[i]);
    }

    return 0;
}
