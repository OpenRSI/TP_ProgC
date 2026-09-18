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
    struct Couleur palette[10] = {
        {0xEF, 0x78, 0x12, 0xFF},
        {0x2C, 0xC8, 0x64, 0xFF},
        {0x11, 0x22, 0x33, 0xFF},
        {0x44, 0x88, 0xCC, 0xFF},
        {0x99, 0x66, 0x33, 0xFF},
        {0x7A, 0x1B, 0x9D, 0xFF},
        {0xF0, 0x0A, 0x5A, 0xFF},
        {0x30, 0x90, 0xF0, 0xFF},
        {0x5A, 0x5A, 0x5A, 0xFF},
        {0x00, 0x00, 0x00, 0xFF}
    };

    for (i = 0; i < 10; ++i)
    {
        printf("Couleur %d : R=%u G=%u B=%u A=%u\n",
               i + 1,
               palette[i].rouge,
               palette[i].vert,
               palette[i].bleu,
               palette[i].alpha);
    }

    return 0;
}
