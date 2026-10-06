#include <stdio.h>

int main(void)
{
    int a = 16;
    int b = 3;

    printf("Addition : %d\n", a + b);
    printf("Soustraction : %d\n", a - b);
    printf("Multiplication : %d\n", a * b);
    /* Deux entiers donnent un quotient entier : 16 / 3 donne 5. */
    printf("Division : %d\n", a / b);
    printf("Reste : %d\n", a % b);
    /* Une comparaison vaut 1 si elle est vraie, sinon 0. */
    printf("a est egal a b : %d\n", a == b);
    printf("a est superieur a b : %d\n", a > b);

    return 0;
}
