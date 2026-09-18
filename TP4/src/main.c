#include "fichier.h"
#include "liste.h"
#include "operator.h"
#include <stdio.h>

static void exercice_4_1(void)
{
    int num1;
    int num2;
    char op;

    printf("Entrez num1 : ");
    scanf("%d", &num1);
    printf("Entrez num2 : ");
    scanf("%d", &num2);
    printf("Entrez l'operateur (+, -, *, /, %%, &, |, ~) : ");
    scanf(" %c", &op);

    if (op == '~')
    {
        printf("Resultat : %d\n", calculer(num1, num2, op));
    }
    else
    {
        printf("Resultat : %d\n", calculer(num1, num2, op));
    }
}

static void exercice_4_2(void)
{
    int choix;
    char nom_fichier[128];
    char message[256];

    printf("Que souhaitez-vous faire ?\n");
    printf("1. Lire un fichier\n");
    printf("2. Ecrire dans un fichier\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    if (choix == 1)
    {
        printf("Entrez le nom du fichier a lire : ");
        scanf("%127s", nom_fichier);
        lire_fichier(nom_fichier);
    }
    else if (choix == 2)
    {
        printf("Entrez le nom du fichier dans lequel vous souhaitez ecrire : ");
        scanf("%127s", nom_fichier);
        printf("Entrez le message a ecrire : ");
        scanf(" %255[^\n]", message);
        ecrire_dans_fichier(nom_fichier, message);
    }
    else
    {
        printf("Choix invalide.\n");
    }
}

static void exercice_4_7(void)
{
    struct couleur *liste = NULL;
    int i;
    unsigned char couleurs[10][4] = {
        {0xEF, 0x78, 0x12, 0xFF},
        {0x2C, 0xC8, 0x64, 0xFF},
        {0x11, 0x22, 0x33, 0xFF},
        {0x44, 0x88, 0xCC, 0xFF},
        {0x99, 0x66, 0x33, 0xFF},
        {0x7A, 0x1B, 0x9D, 0xFF},
        {0xF0, 0x0A, 0x5A, 0xFF},
        {0x30, 0x90, 0xF0, 0xFF},
        {0x5A, 0x5A, 0x5A, 0xFF},
        {0x00, 0x00, 0x00, 0xFF}
    };

    for (i = 0; i < 10; ++i)
    {
        insertion(&liste, couleurs[i][0], couleurs[i][1], couleurs[i][2], couleurs[i][3]);
    }

    parcours(liste);
}

int main(void)
{
    int choix;

    printf("Choisissez un exercice (1, 2, 7, 0 pour quitter) : ");
    scanf("%d", &choix);

    switch (choix)
    {
        case 1:
            exercice_4_1();
            break;
        case 2:
            exercice_4_2();
            break;
        case 7:
            exercice_4_7();
            break;
        case 0:
            printf("Fin du programme.\n");
            return 0;
        default:
            printf("Choix invalide.\n");
            break;
    }

    return 0;
}
