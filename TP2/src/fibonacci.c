#include <stdio.h>

int main(void)
{
    int n;
    int i;
    unsigned long long u0 = 0;
    unsigned long long u1 = 1;
    unsigned long long temp;

    printf("Entrez n : ");
    if (scanf("%d", &n) != 1)
    {
        printf("Valeur invalide.\n");
        return 1;
    }

    if (n < 0)
    {
        printf("n doit etre positif ou nul.\n");
        return 1;
    }

    printf("%llu", u0);
    for (i = 1; i < n; ++i)
    {
        printf(", %llu", u1);
        temp = u0 + u1;
        u0 = u1;
        u1 = temp;
    }

    printf("\n");
    return 0;
}
