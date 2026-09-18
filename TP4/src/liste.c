#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

void insertion(struct couleur **liste, unsigned char r, unsigned char v, unsigned char b, unsigned char a)
{
    struct couleur *nouveau = malloc(sizeof(struct couleur));
    if (nouveau == NULL)
    {
        printf("Erreur de memoire.\n");
        return;
    }

    nouveau->rouge = r;
    nouveau->vert = v;
    nouveau->bleu = b;
    nouveau->alpha = a;
    nouveau->suivant = *liste;
    *liste = nouveau;
}

void parcours(const struct couleur *liste)
{
    const struct couleur *courant = liste;
    int i = 1;

    while (courant != NULL)
    {
        printf("Couleur %d : R=%u G=%u B=%u A=%u\n",
               i,
               courant->rouge,
               courant->vert,
               courant->bleu,
               courant->alpha);
        courant = courant->suivant;
        ++i;
    }
}
