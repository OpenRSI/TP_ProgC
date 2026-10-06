#include <stdio.h>
#include <stddef.h>

/* Lire par unsigned char permet d'inspecter les octets de n'importe quel type.
   L'affichage suit l'ordre des adresses memoire croissantes, octet par octet.
   Des octets de bourrage, notamment de long double, peuvent varier. */
static void afficher(const char *nom, const void *adresse, size_t taille)
{
    const unsigned char *octets = adresse;
    printf("%s : adresse = %p, octets hex =", nom, (void *)adresse);
    for (size_t i = 0; i < taille; i++) {
        printf(" %02x", (unsigned int)*(octets + i));
    }
    printf("\n");
}

int main(void)
{
    /* On reprend les variables de l'exercice 1.4. */
    char caractere = 'A';
    signed char petit_entier = -10;
    unsigned char petit_naturel = 200;
    signed short entier_court = -1000;
    unsigned short naturel_court = 1000;
    signed int entier = -42;
    unsigned int naturel = 42U;
    signed long int entier_long = -100000L;
    unsigned long int naturel_long = 100000UL;
    signed long long int entier_tres_long = -10000000000LL;
    unsigned long long int naturel_tres_long = 10000000000ULL;
    float reel_simple = 3.14f;
    double reel_double = 3.14159;
    long double reel_long = 3.141592653589793238L;

    /* & recupere l'adresse ; le type du pointeur correspond au type pointe. */
    char *p_caractere = &caractere;
    signed char *p_petit_entier = &petit_entier;
    unsigned char *p_petit_naturel = &petit_naturel;
    signed short *p_entier_court = &entier_court;
    unsigned short *p_naturel_court = &naturel_court;
    signed int *p_entier = &entier;
    unsigned int *p_naturel = &naturel;
    signed long int *p_entier_long = &entier_long;
    unsigned long int *p_naturel_long = &naturel_long;
    signed long long int *p_entier_tres_long = &entier_tres_long;
    unsigned long long int *p_naturel_tres_long = &naturel_tres_long;
    float *p_reel_simple = &reel_simple;
    double *p_reel_double = &reel_double;
    long double *p_reel_long = &reel_long;

    printf("Avant la manipulation :\n");
    afficher("caractere", p_caractere, sizeof(caractere));
    afficher("petit_entier", p_petit_entier, sizeof(petit_entier));
    afficher("petit_naturel", p_petit_naturel, sizeof(petit_naturel));
    afficher("entier_court", p_entier_court, sizeof(entier_court));
    afficher("naturel_court", p_naturel_court, sizeof(naturel_court));
    afficher("entier", p_entier, sizeof(entier));
    afficher("naturel", p_naturel, sizeof(naturel));
    afficher("entier_long", p_entier_long, sizeof(entier_long));
    afficher("naturel_long", p_naturel_long, sizeof(naturel_long));
    afficher("entier_tres_long", p_entier_tres_long, sizeof(entier_tres_long));
    afficher("naturel_tres_long", p_naturel_tres_long, sizeof(naturel_tres_long));
    afficher("reel_simple", p_reel_simple, sizeof(reel_simple));
    afficher("reel_double", p_reel_double, sizeof(reel_double));
    afficher("reel_long", p_reel_long, sizeof(reel_long));

    /* *p modifie la variable situee a cette adresse. */
    *p_caractere = 'B';
    *p_petit_entier = -9;
    *p_petit_naturel = 201;
    *p_entier_court = -999;
    *p_naturel_court = 1001;
    *p_entier = -41;
    *p_naturel = 43U;
    *p_entier_long = -99999L;
    *p_naturel_long = 100001UL;
    *p_entier_tres_long = -9999999999LL;
    *p_naturel_tres_long = 10000000001ULL;
    *p_reel_simple = 2.0f;
    *p_reel_double = 2.0;
    *p_reel_long = 2.0L;

    printf("\nApres la manipulation :\n");
    afficher("caractere", p_caractere, sizeof(caractere));
    afficher("petit_entier", p_petit_entier, sizeof(petit_entier));
    afficher("petit_naturel", p_petit_naturel, sizeof(petit_naturel));
    afficher("entier_court", p_entier_court, sizeof(entier_court));
    afficher("naturel_court", p_naturel_court, sizeof(naturel_court));
    afficher("entier", p_entier, sizeof(entier));
    afficher("naturel", p_naturel, sizeof(naturel));
    afficher("entier_long", p_entier_long, sizeof(entier_long));
    afficher("naturel_long", p_naturel_long, sizeof(naturel_long));
    afficher("entier_tres_long", p_entier_tres_long, sizeof(entier_tres_long));
    afficher("naturel_tres_long", p_naturel_tres_long, sizeof(naturel_tres_long));
    afficher("reel_simple", p_reel_simple, sizeof(reel_simple));
    afficher("reel_double", p_reel_double, sizeof(reel_double));
    afficher("reel_long", p_reel_long, sizeof(reel_long));

    return 0;
}
