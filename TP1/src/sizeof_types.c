#include <stdio.h>

int main() {
    printf("=== Tailles des types de base en C ===\n\n");

    // char
    printf("signed char       : %zu octets\n", sizeof(signed char));
    printf("unsigned char     : %zu octets\n", sizeof(unsigned char));
    printf("char              : %zu octets\n\n", sizeof(char));

    // short
    printf("signed short      : %zu octets\n", sizeof(signed short));
    printf("unsigned short    : %zu octets\n", sizeof(unsigned short));
    printf("short             : %zu octets\n\n", sizeof(short));

    // int
    printf("signed int        : %zu octets\n", sizeof(signed int));
    printf("unsigned int      : %zu octets\n", sizeof(unsigned int));
    printf("int               : %zu octets\n\n", sizeof(int));

    // long int
    printf("signed long int   : %zu octets\n", sizeof(signed long int));
    printf("unsigned long int : %zu octets\n", sizeof(unsigned long int));
    printf("long int          : %zu octets\n\n", sizeof(long int));

    // long long int
    printf("signed long long int   : %zu octets\n", sizeof(signed long long int));
    printf("unsigned long long int : %zu octets\n", sizeof(unsigned long long int));
    printf("long long int          : %zu octets\n\n", sizeof(long long int));

    // Types flottants (pas de versions signed/unsigned)
    printf("float             : %zu octets\n", sizeof(float));
    printf("double            : %zu octets\n", sizeof(double));
    printf("long double       : %zu octets\n", sizeof(long double));

    return 0;
}
