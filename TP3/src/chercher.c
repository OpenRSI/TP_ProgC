#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int tab[100];
    int i;
    int valeur;
    int present = 0;

    srand((unsigned int)time(NULL));

    for (i = 0; i < 100; ++i)
    {
        tab[i] = rand() % 200 - 100;
    }

    printf("Tableau :\n");
    for (i = 0; i < 100; ++i)
    {
        printf("%d%s", tab[i], (i == 99) ? "\n" : " ");
    }

    printf("Entrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &valeur);

    for (i = 0; i < 100; ++i)
    {
        if (tab[i] == valeur)
        {
            present = 1;
            break;
        }
    }

    if (present)
    {
        printf("Resultat : entier present\n");
    }
    else
    {
        printf("Resultat : entier absent\n");
    }

    return 0;
}
