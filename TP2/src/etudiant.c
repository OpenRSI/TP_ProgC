#include <stdio.h>

int main(void)
{
    /* Donnees fictives : un meme indice relie les informations d'un etudiant. */
    char identites[5][2][32] = {
        {"Dupont", "Marie"}, {"Martin", "Pierre"}, {"Bernard", "Alice"},
        {"Petit", "Lucas"}, {"Robert", "Emma"}
    };
    char adresses[5][80] = {
        "20, Boulevard Niels Bohr, Lyon", "22, Boulevard Niels Bohr, Lyon",
        "1, Rue des Ecoles, Lyon", "2, Rue des Ecoles, Lyon",
        "3, Rue des Ecoles, Lyon"
    };
    float notes_c[5] = {16.5f, 14.0f, 15.0f, 12.5f, 18.0f};
    float notes_systeme[5] = {12.1f, 14.1f, 16.0f, 13.5f, 17.0f};

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d :\n", i + 1);
        printf("Nom : %s\n", identites[i][0]);
        printf("Prenom : %s\n", identites[i][1]);
        printf("Adresse : %s\n", adresses[i]);
        printf("Programmation en C : %.1f\n", notes_c[i]);
        printf("Systeme d'exploitation : %.1f\n\n", notes_systeme[i]);
    }
    return 0;
}
