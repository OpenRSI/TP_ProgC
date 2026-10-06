#include <stdio.h>

int main(void)
{
    int a = 2;
    int b = 3;
    long long resultat = 1;

    /* Cette version calcule des puissances entieres d'exposant positif ou nul. */
    if (b < 0) {
        printf("L'exposant doit etre positif ou nul.\n");
        return 1;
    }
    /* Partir de 1 permet aussi de calculer a puissance 0. */
    for (int i = 0; i < b; i++) {
        resultat *= a;
    }
    printf("%d puissance %d = %lld\n", a, b, resultat);
    return 0;
}
