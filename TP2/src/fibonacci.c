#include <stdio.h>

int main(void)
{
    int n;
    unsigned long long precedent = 0;
    unsigned long long courant = 1;

    /* U93 tient encore dans un entier non signe de 64 bits. */
    printf("Indice du dernier terme (0 a 93) : ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 93) {
        printf("Veuillez entrer un entier entre 0 et 93.\n");
        return 1;
    }

    /* On suit la definition U0 a Un : cela fait n + 1 termes. */
    printf("U0 a U%d : 0", n);
    for (int i = 1; i <= n; i++) {
        printf(", %llu", courant);
        if (i < n) {
            unsigned long long suivant = precedent + courant;
            precedent = courant;
            courant = suivant;
        }
    }
    printf("\n");
    return 0;
}
