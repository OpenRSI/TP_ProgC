#include <stdio.h>

int main(void)
{
    int d = (1 << 28) | (1 << 12);
    int bit4 = (d >> 28) & 1;
    int bit20 = (d >> 12) & 1;

    printf("%d\n", bit4 && bit20);
    return 0;
}
