#include <stdio.h>

long long factorielle(int n)
{
    if (n < 0)
    {
        return -1;
    }
    if (n == 0 || n == 1)
    {
        return 1;
    }
    return n * factorielle(n - 1);
}

int main(void)
{
    int valeurs[] = {0, 1, 5, 10};
    int i;

    for (i = 0; i < 4; ++i)
    {
        printf("fact(%d) = %lld\n", valeurs[i], factorielle(valeurs[i]));
    }
    return 0;
}
