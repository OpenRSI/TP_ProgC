#include <stdio.h>

int main(void) {
    int nombres[5] = {0, 4096, 65536, 65535, 1024};
    int i;
    int j;
    int nombre;
    int bits[32];

    for (i = 0; i < 5; i++) {
        nombre = nombres[i];

        printf("%d en binaire : ", nombre);

        /* Cas particulier : 0 */
        if (nombre == 0) {
            printf("0\n");
            continue;
        }

        /*
         * On obtient les bits avec le reste de la division par 2.
         * Ils sont stockes a l'envers dans le tableau bits.
         */
        for (j = 0; nombre > 0; j++) {
            bits[j] = nombre % 2;
            nombre = nombre / 2;
        }

        /* On affiche les bits dans le bon ordre */
        for (j = j - 1; j >= 0; j--) {
            printf("%d", bits[j]);
        }

        printf("\n");
    }

    return 0;
}