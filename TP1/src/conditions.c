#include <stdio.h>

int main(void)
{
    int somme = 0;

    for (int nombre = 1; nombre <= 1000; nombre++) {
        /* Les multiples de 11 sont exclus avant toute addition. */
        if (nombre % 11 == 0) {
            continue;
        }
        /* || signifie OU : un multiple de 5 et de 7 est ajoute une seule fois. */
        if (nombre % 5 == 0 || nombre % 7 == 0) {
            somme += nombre;
        }
        if (somme > 5000) {
            break;
        }
    }

    printf("Somme finale : %d\n", somme);
    return 0;
}
