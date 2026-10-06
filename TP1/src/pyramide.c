#include <stdio.h>

int main(void)
{
    int n = 5;
    int i;
    int j;

    /* Chaque nombre reste sur un chiffre pour conserver le motif. */
    if (n < 1 || n > 9) {
        printf("La hauteur doit etre comprise entre 1 et 9.\n");
        return 1;
    }

    for (i = 1; i <= n; i++) {
        /* Moins d'espaces a chaque nouvelle ligne. */
        for (j = 0; j < n - i; j++) {
            printf(" ");
        }
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }
        /* Commence a i - 1 pour ne pas repeter le sommet. */
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }
        printf("\n");
    }

    printf("Generation de la pyramide terminee.\n");
    return 0;
}
