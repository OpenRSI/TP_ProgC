#ifndef LISTE_H
#define LISTE_H

struct couleur
{
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    unsigned char alpha;
    struct couleur *suivant;
};

void insertion(struct couleur **liste, unsigned char r, unsigned char v, unsigned char b, unsigned char a);
void parcours(const struct couleur *liste);

#endif
