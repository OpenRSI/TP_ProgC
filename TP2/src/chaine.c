#include <stdio.h>

int main(void)
{
    char premiere[] = "Hello";
    char seconde[] = " World!";
    /* sizeof inclut le caractere final '\0' des chaines initialisees. */
    char copie[sizeof(premiere)];
    char concatenation[sizeof(premiere) + sizeof(seconde) - 1];
    unsigned int longueur1 = 0;
    unsigned int longueur2 = 0;
    unsigned int i;

    /* Aucun appel a une fonction de manipulation de chaines. */
    while (premiere[longueur1] != '\0') {
        longueur1++;
    }
    while (seconde[longueur2] != '\0') {
        longueur2++;
    }

    for (i = 0; i < longueur1; i++) {
        copie[i] = premiere[i];
        concatenation[i] = premiere[i];
    }
    copie[longueur1] = '\0';

    /* La seconde chaine commence juste apres les caracteres de la premiere. */
    for (i = 0; i < longueur2; i++) {
        concatenation[longueur1 + i] = seconde[i];
    }
    concatenation[longueur1 + longueur2] = '\0';

    printf("Longueur de la premiere chaine : %u\n", longueur1);
    printf("Longueur de la seconde chaine : %u\n", longueur2);
    printf("Longueur totale : %u\n", longueur1 + longueur2);
    printf("Copie : %s\n", copie);
    printf("Concatenation : %s\n", concatenation);
    return 0;
}
