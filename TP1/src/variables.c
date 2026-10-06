#include <stdio.h>

int main(void)
{
    /* signed accepte les valeurs negatives ; unsigned reste positif ou nul. */
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

    /* Chaque format de printf correspond au type de la variable. */
    printf("char : %c\n", caractere);
    printf("signed char : %hhd\n", petit_entier);
    printf("unsigned char : %hhu\n", petit_naturel);
    printf("signed short : %hd\n", entier_court);
    printf("unsigned short : %hu\n", naturel_court);
    printf("signed int : %d\n", entier);
    printf("unsigned int : %u\n", naturel);
    printf("signed long int : %ld\n", entier_long);
    printf("unsigned long int : %lu\n", naturel_long);
    printf("signed long long int : %lld\n", entier_tres_long);
    printf("unsigned long long int : %llu\n", naturel_tres_long);
    printf("float : %.2f\n", reel_simple);
    printf("double : %.5f\n", reel_double);
    printf("long double : %.18Lf\n", reel_long);

    return 0;
}
