#include <stdio.h>

int main(void) {
    int compteur = 9;
    int ligne;
    int colonne;

    if (compteur <= 0 || compteur >= 10) {
        printf("Le compteur doit etre entre 1 et 9.\n");
        return 1;
    }

    for (ligne = 1; ligne <= compteur; ligne++) {
        for (colonne = 1; colonne <= ligne; colonne++) {
            if (ligne == 1 || ligne == compteur ||
                colonne == 1 || colonne == ligne) {
                printf("* ");
            } else {
                printf("# ");
            }
        }

        printf("\n");
    }

    return 0;
}