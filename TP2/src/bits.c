#include <stdio.h>
#include <limits.h>

int main(void)
{
    /* On compte depuis le bit le plus a gauche, sur toute la largeur du type. */
    unsigned int largeur = sizeof(unsigned int) * CHAR_BIT;
    if (largeur < 20) {
        printf("Ce type doit contenir au moins 20 bits.\n");
        return 1;
    }

    /* 1U permet de decaler un entier non signe sans toucher un bit de signe. */
    unsigned int masque4 = 1U << (largeur - 4);
    unsigned int masque20 = 1U << (largeur - 20);
    unsigned int d = masque4 | masque20;
    unsigned int bit4 = (d >> (largeur - 4)) & 1U;
    unsigned int bit20 = (d >> (largeur - 20)) & 1U;

    printf("%d\n", bit4 == 1 && bit20 == 1);
    return 0;
}
