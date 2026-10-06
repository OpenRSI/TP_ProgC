#include <stdio.h>

int main(void) {
    int nombre;
    int somme = 0;

    for (nombre = 1; nombre <= 1000; nombre++) {

        /* Si divisible par 11, on passe au nombre suivant */
        if (nombre % 11 == 0) {
            continue;
        }

        /* Si divisible par 5 OU par 7, on l'ajoute */
        if (nombre % 5 == 0 || nombre % 7 == 0) {
            somme = somme + nombre;
        }

        /* Si la somme dépasse 5000, on arrête */
        if (somme > 5000) {
            break;
        }
    }

    printf("Somme finale : %d\n", somme);

    return 0;
}