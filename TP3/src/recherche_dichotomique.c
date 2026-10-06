#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int rechercheDichotomique(const int *tab, int taille, int valeur)
{
    int gauche = 0;
    int droite = taille - 1;
    int milieu;

    while (gauche <= droite)
    {
        milieu = gauche + (droite - gauche) / 2;

        if (tab[milieu] == valeur)
        {
            return 1;
        }
        if (tab[milieu] < valeur)
        {
            gauche = milieu + 1;
        }
        else
        {
            droite = milieu - 1;
        }
    }

    return 0;
}

int main(void)
{
    int tab[100];
    int i;
    int valeur;

    srand((unsigned int)time(NULL));

    for (i = 0; i < 100; ++i)
    {
        tab[i] = rand() % 200 - 100;
    }

    trierCroissant(tab, 100);

    printf("Tableau trie :\n");
    for (i = 0; i < 100; ++i)
    {
        printf("%d%s", tab[i], (i == 99) ? "\n" : " ");
    }

    printf("Entrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &valeur);

    if (rechercheDichotomique(tab, 100, valeur))
    {
        printf("Resultat : entier present\n");
    }
    else
    {
        printf("Resultat : entier absent\n");
    }

    return 0;
}
