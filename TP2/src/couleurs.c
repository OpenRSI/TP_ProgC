#include <stdio.h>

struct Couleur
{
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    unsigned char alpha;
};

int main(void)
{
    int i;
    struct Couleur couleurs[10] = {
        {0xef, 0x78, 0x12, 0xff},
        {0x2c, 0xc8, 0x64, 0xff},
        {0x11, 0x22, 0x33, 0xff},
        {0x44, 0x88, 0xcc, 0xff},
        {0x99, 0x66, 0x33, 0xff},
        {0x7a, 0x1b, 0x9d, 0xff},
        {0xf0, 0x0a, 0x5a, 0xff},
        {0x30, 0x90, 0xf0, 0xff},
        {0x5a, 0x5a, 0x5a, 0xff},
        {0x00, 0x00, 0x00, 0xff}
    };

    for (i = 0; i < 10; ++i)
    {
        printf("Couleur %d :\n", i + 1);
        printf("Rouge : %u\n", couleurs[i].rouge);
        printf("Vert : %u\n", couleurs[i].vert);
        printf("Bleu : %u\n", couleurs[i].bleu);
        printf("Alpha : %u\n\n", couleurs[i].alpha);
    }

    return 0;
}
