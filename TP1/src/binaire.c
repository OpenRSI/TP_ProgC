#include <stdio.h>
#include <limits.h>

int main(void)
{
    int nombres[] = {0, 4096, 65536, 65535, 1024};

    for (unsigned int i = 0; i < sizeof(nombres) / sizeof(nombres[0]); i++) {
        int nombre = nombres[i];
        /* Assez de places pour tous les bits d'un int. */
        int chiffres[sizeof(int) * CHAR_BIT];
        int taille = 0;

        printf("%d : ", nombre);
        if (nombre == 0) {
            printf("0\n");
            continue;
        }

        /* Les restes arrivent du bit de droite vers le bit de gauche. */
        for (int quotient = nombre; quotient > 0; quotient /= 2) {
            chiffres[taille] = quotient % 2;
            taille++;
        }
        /* On les affiche a l'envers pour retrouver l'ordre habituel. */
        for (int j = taille - 1; j >= 0; j--) {
            printf("%d", chiffres[j]);
        }
        printf("\n");
    }

    return 0;
}
