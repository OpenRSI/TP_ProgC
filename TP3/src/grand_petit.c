#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int tab[100];
    int i;
    int plusGrand;
    int plusPetit;

    srand((unsigned int)time(NULL));

    for (i = 0; i < 100; ++i)
    {
        tab[i] = rand() % 1000 + 1;
    }

    plusGrand = tab[0];
    plusPetit = tab[0];

    for (i = 1; i < 100; ++i)
    {
        if (tab[i] > plusGrand)
        {
            plusGrand = tab[i];
        }
        if (tab[i] < plusPetit)
        {
            plusPetit = tab[i];
        }
    }

    printf("Le nombre le plus grand est : %d\n", plusGrand);
    printf("Le nombre le plus petit est : %d\n", plusPetit);
    return 0;
}
