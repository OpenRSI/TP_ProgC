#include <stdio.h>

int main(void) {
    char lettre = 'A';
    signed char petit_nombre = -100;
    unsigned char petit_nombre_positif = 200;

    short nombre_court = -32000;
    unsigned short nombre_court_positif = 65000;

    int nombre = -2000000000;
    unsigned int nombre_positif = 4000000000U;

    long int grand_nombre = -1000000L;
    unsigned long int grand_nombre_positif = 1000000UL;

    long long int tres_grand_nombre = -9000000000LL;
    unsigned long long int tres_grand_nombre_positif = 18000000000ULL;

    float prix = 12.5f;
    double moyenne = 15.75;
    long double resultat = 3.141592L;

    printf("char : %c\n", lettre);
    printf("signed char : %hhd\n", petit_nombre);
    printf("unsigned char : %hhu\n", petit_nombre_positif);

    printf("short : %hd\n", nombre_court);
    printf("unsigned short : %hu\n", nombre_court_positif);

    printf("int : %d\n", nombre);
    printf("unsigned int : %u\n", nombre_positif);

    printf("long int : %ld\n", grand_nombre);
    printf("unsigned long int : %lu\n", grand_nombre_positif);

    printf("long long int : %lld\n", tres_grand_nombre);
    printf("unsigned long long int : %llu\n", tres_grand_nombre_positif);

    printf("float : %.2f\n", prix);
    printf("double : %.2f\n", moyenne);
    printf("long double : %.6Lf\n", resultat);

    return 0;
}