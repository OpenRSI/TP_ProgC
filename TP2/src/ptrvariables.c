#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    char c = 'A';
    short s = 12;
    int i = 42;
    long l = 123456L;
    long long ll = 987654321LL;
    float f = 3.5f;
    double d = 1.25;
    long double ld = 2.75L;

    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long *pl = &l;
    long long *pll = &ll;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    printf("Avant la manipulation :\n");
    printf("Adresse de c : %p, Valeur de c : 0x%02X\n", (void *)pc, (unsigned char)*pc);
    printf("Adresse de s : %p, Valeur de s : 0x%04X\n", (void *)ps, (unsigned short)*ps);
    printf("Adresse de i : %p, Valeur de i : 0x%08X\n", (void *)pi, (unsigned int)*pi);
    printf("Adresse de l : %p, Valeur de l : 0x%016lX\n", (void *)pl, (unsigned long)*pl);
    printf("Adresse de ll : %p, Valeur de ll : 0x%016llX\n", (void *)pll, (unsigned long long)*pll);

    {
        uint32_t bits;
        memcpy(&bits, pf, sizeof(*pf));
        printf("Adresse de f : %p, Valeur de f : 0x%08X\n", (void *)pf, bits);
    }

    {
        uint64_t bits;
        memcpy(&bits, pd, sizeof(*pd));
        printf("Adresse de d : %p, Valeur de d : 0x%016llX\n", (void *)pd, (unsigned long long)bits);
    }

    {
        unsigned char bytes[sizeof(long double)];
        memcpy(bytes, pld, sizeof(long double));
        printf("Adresse de ld : %p, Valeur de ld : ", (void *)pld);
        for (size_t j = 0; j < sizeof(long double); ++j)
        {
            printf("%02X", bytes[j]);
        }
        printf("\n");
    }

    *pc = 'Z';
    *ps = 20;
    *pi = 99;
    *pl = 987654321L;
    *pll = 1234567890123LL;
    *pf = 2.5f;
    *pd = 3.75;
    *pld = 4.5L;

    printf("\nApres la manipulation :\n");
    printf("Adresse de c : %p, Valeur de c : 0x%02X\n", (void *)pc, (unsigned char)*pc);
    printf("Adresse de s : %p, Valeur de s : 0x%04X\n", (void *)ps, (unsigned short)*ps);
    printf("Adresse de i : %p, Valeur de i : 0x%08X\n", (void *)pi, (unsigned int)*pi);
    printf("Adresse de l : %p, Valeur de l : 0x%016lX\n", (void *)pl, (unsigned long)*pl);
    printf("Adresse de ll : %p, Valeur de ll : 0x%016llX\n", (void *)pll, (unsigned long long)*pll);

    {
        uint32_t bits;
        memcpy(&bits, pf, sizeof(*pf));
        printf("Adresse de f : %p, Valeur de f : 0x%08X\n", (void *)pf, bits);
    }

    {
        uint64_t bits;
        memcpy(&bits, pd, sizeof(*pd));
        printf("Adresse de d : %p, Valeur de d : 0x%016llX\n", (void *)pd, (unsigned long long)bits);
    }

    {
        unsigned char bytes[sizeof(long double)];
        memcpy(bytes, pld, sizeof(long double));
        printf("Adresse de ld : %p, Valeur de ld : ", (void *)pld);
        for (size_t j = 0; j < sizeof(long double); ++j)
        {
            printf("%02X", bytes[j]);
        }
        printf("\n");
    }

    return 0;
}
