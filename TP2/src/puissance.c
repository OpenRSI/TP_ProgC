#include <stdio.h>

int main(void)
{
    int a = 2;
    int b = 3;
    long long resultat = 1;
    int i;

    for (i = 0; i < b; ++i)
    {
        resultat *= a;
    }

    printf("%d^%d = %lld\n", a, b, resultat);
    return 0;
}
