#include <stdio.h>
#include <string.h>

struct Etudiant {
    char nom[32];
    char prenom[32];
    char adresse[80];
    float note_c;
    float note_systeme;
};

int main(void)
{
    struct Etudiant etudiants[5];
    /* Donnees fictives et suffisamment courtes pour les tableaux destinations. */
    const char *noms[5] = {"Dupont", "Martin", "Bernard", "Petit", "Robert"};
    const char *prenoms[5] = {"Marie", "Pierre", "Alice", "Lucas", "Emma"};
    const char *adresses[5] = {
        "20, Boulevard Niels Bohr, Lyon", "22, Boulevard Niels Bohr, Lyon",
        "1, Rue des Ecoles, Lyon", "2, Rue des Ecoles, Lyon",
        "3, Rue des Ecoles, Lyon"
    };
    float notes_c[5] = {16.5f, 14.0f, 15.0f, 12.5f, 18.0f};
    float notes_systeme[5] = {12.1f, 14.1f, 16.0f, 13.5f, 17.0f};

    for (int i = 0; i < 5; i++) {
        /* strcpy copie les caracteres ET le '\0' de fin. */
        strcpy(etudiants[i].nom, noms[i]);
        strcpy(etudiants[i].prenom, prenoms[i]);
        strcpy(etudiants[i].adresse, adresses[i]);
        etudiants[i].note_c = notes_c[i];
        etudiants[i].note_systeme = notes_systeme[i];
    }

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d :\n", i + 1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prenom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Programmation en C : %.1f\n", etudiants[i].note_c);
        printf("Systeme d'exploitation : %.1f\n\n", etudiants[i].note_systeme);
    }
    return 0;
}
