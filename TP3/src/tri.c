#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void afficherTableau(const int *tab, int taille)
{
    int i;
    for (i = 0; i < taille; ++i)
    {
        printf("%d%s", tab[i], (i == taille - 1) ? "\n" : " ");
    }
}

void trierCroissant(int *tab, int taille)
{
    int i;
    int j;
    int temp;

    for (i = 0; i < taille - 1; ++i)
    {
        for (j = 0; j < taille - i - 1; ++j)
        {
            if (tab[j] > tab[j + 1])
            {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    int tab[100];
    int i;

    srand((unsigned int)time(NULL));

    for (i = 0; i < 100; ++i)
    {
        tab[i] = rand() % 200 - 100;
    }

    printf("Tableau non trie :\n");
    afficherTableau(tab, 100);

    trierCroissant(tab, 100);

    printf("Tableau trie par ordre croissant :\n");
    afficherTableau(tab, 100);
    return 0;
}
