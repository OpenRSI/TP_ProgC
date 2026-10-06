#include <stdio.h>

struct Couleur {
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    unsigned char alpha;
};

int main(void)
{
    /* Un composant occupe un octet. 0xff vaut 255. */
    struct Couleur couleurs[10] = {
        {0xef, 0x78, 0x12, 0xff}, {0x2c, 0xc8, 0x64, 0xff},
        {0xff, 0x00, 0x00, 0xff}, {0x00, 0xff, 0x00, 0xff},
        {0x00, 0x00, 0xff, 0xff}, {0xff, 0xff, 0x00, 0xff},
        {0x00, 0xff, 0xff, 0xff}, {0xff, 0x00, 0xff, 0xff},
        {0x00, 0x00, 0x00, 0xff}, {0xff, 0xff, 0xff, 0x80}
    };

    for (int i = 0; i < 10; i++) {
        printf("Couleur %d :\n", i + 1);
        printf("Rouge : %hhu\n", couleurs[i].rouge);
        printf("Vert : %hhu\n", couleurs[i].vert);
        printf("Bleu : %hhu\n", couleurs[i].bleu);
        printf("Alpha : %hhu\n\n", couleurs[i].alpha);
    }
    return 0;
}
