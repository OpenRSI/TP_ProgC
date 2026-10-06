#include <stdio.h>

void afficherOctets(const void *ptr, size_t taille)
{
    const unsigned char *octets = (const unsigned char *)ptr;
    size_t i;

    for (i = 0; i < taille; ++i)
    {
        printf("%02X ", octets[i]);
    }
    printf("\n");
}

int main(void)
{
    short s = 0x0102;
    int i = 0x01020304;
    long int li = 0x0102030405060708L;
    float f = 1.5f;
    double d = 1.5;
    long double ld = 1.5L;

    printf("Octets de short :\n");
    afficherOctets(&s, sizeof(s));

    printf("Octets de int :\n");
    afficherOctets(&i, sizeof(i));

    printf("Octets de long int :\n");
    afficherOctets(&li, sizeof(li));

    printf("Octets de float :\n");
    afficherOctets(&f, sizeof(f));

    printf("Octets de double :\n");
    afficherOctets(&d, sizeof(d));

    printf("Octets de long double :\n");
    afficherOctets(&ld, sizeof(ld));

    return 0;
}
