#include <stdio.h>

struct Couleur
{
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    unsigned char alpha;
};

struct CouleurComptee
{
    struct Couleur couleur;
    int count;
};

int couleurExiste(const struct CouleurComptee *tab, int taille, struct Couleur c)
{
    int i;

    for (i = 0; i < taille; ++i)
    {
        if (tab[i].couleur.rouge == c.rouge &&
            tab[i].couleur.vert == c.vert &&
            tab[i].couleur.bleu == c.bleu &&
            tab[i].couleur.alpha == c.alpha)
        {
            return i;
        }
    }

    return -1;
}

int main(void)
{
    struct Couleur couleurs[100];
    struct CouleurComptee distinct[100];
    int nombreDistinct = 0;
    int i;

    for (i = 0; i < 100; ++i)
    {
        couleurs[i].rouge = (unsigned char)((i * 17) % 256);
        couleurs[i].vert = (unsigned char)((i * 29) % 256);
        couleurs[i].bleu = (unsigned char)((i * 41) % 256);
        couleurs[i].alpha = 0xFF;

        int index = couleurExiste(distinct, nombreDistinct, couleurs[i]);
        if (index == -1)
        {
            distinct[nombreDistinct].couleur = couleurs[i];
            distinct[nombreDistinct].count = 1;
            nombreDistinct++;
        }
        else
        {
            distinct[index].count++;
        }
    }

    for (i = 0; i < nombreDistinct; ++i)
    {
        printf("%02X %02X %02X %02X : %d\n",
               distinct[i].couleur.rouge,
               distinct[i].couleur.vert,
               distinct[i].couleur.bleu,
               distinct[i].couleur.alpha,
               distinct[i].count);
    }

    return 0;
}
