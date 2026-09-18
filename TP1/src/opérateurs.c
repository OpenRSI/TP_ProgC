#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int a = 16;
    int b = 3;

    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);
    printf("a %% b = %d\n", a % b);

    bool egal = (a == b);
    bool superieur = (a > b);

    printf("a est egal a b : %d\n", egal);
    printf("a est superieur a b : %d\n", superieur);

    return 0;
}