#include <stdio.h>

int main() {
    printf("Tailles des types de base en C (en octets) :\n\n");

    // Types caractères
    printf("char (signed)        : %zu octet(s)\n", sizeof(signed char));
    printf("char (unsigned)      : %zu octet(s)\n", sizeof(unsigned char));

    // Types entiers courts
    printf("short (signed)       : %zu octet(s)\n", sizeof(signed short));
    printf("short (unsigned)     : %zu octet(s)\n", sizeof(unsigned short));

    // Types entiers
    printf("int (signed)         : %zu octet(s)\n", sizeof(signed int));
    printf("int (unsigned)       : %zu octet(s)\n", sizeof(unsigned int));

    // Types long
    printf("long int (signed)    : %zu octet(s)\n", sizeof(signed long int));
    printf("long int (unsigned)  : %zu octet(s)\n", sizeof(unsigned long int));

    // Types long long
    printf("long long (signed)   : %zu octet(s)\n", sizeof(signed long long int));
    printf("long long (unsigned) : %zu octet(s)\n", sizeof(unsigned long long int));

    // Types à virgule flottante
    printf("float                : %zu octet(s)\n", sizeof(float));
    printf("double               : %zu octet(s)\n", sizeof(double));
    printf("long double          : %zu octet(s)\n", sizeof(long double));

    return 0;
}
