#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int entiers[11];
    float reels[11];
    int taille = 11;

    srand((unsigned int)time(NULL));
    /* Les crochets servent uniquement a declarer les tableaux. */
    for (int i = 0; i < taille; i++) {
        *(entiers + i) = rand() % 101;
        *(reels + i) = (rand() % 1001) / 100.0f;
    }

    printf("Entiers avant :\n");
    for (int *p = entiers; p < entiers + taille; p++) {
        printf("%d ", *p);
    }
    printf("\nReels avant :\n");
    for (float *p = reels; p < reels + taille; p++) {
        printf("%.2f ", *p);
    }

    /* Les indices commencent a 0 : on modifie 0, 2, 4, 6, 8 et 10. */
    for (int i = 0; i < taille; i++) {
        if (i % 2 == 0) {
            *(entiers + i) *= 3;
            *(reels + i) *= 3;
        }
    }

    printf("\nEntiers apres :\n");
    for (int *p = entiers; p < entiers + taille; p++) {
        printf("%d ", *p);
    }
    printf("\nReels apres :\n");
    for (float *p = reels; p < reels + taille; p++) {
        printf("%.2f ", *p);
    }
    printf("\n");
    return 0;
}
