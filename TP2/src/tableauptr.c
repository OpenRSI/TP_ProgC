#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int tabInt[10];
    float tabFloat[10];
    int *pInt = tabInt;
    float *pFloat = tabFloat;
    int i;

    srand((unsigned int)time(NULL));

    for (i = 0; i < 10; ++i, ++pInt, ++pFloat)
    {
        *pInt = rand() % 100;
        *pFloat = (float)(rand() % 100) / 10.0f;
    }

    printf("Tableau d'entiers (avant) : ");
    for (i = 0; i < 10; ++i)
    {
        printf("%d%s", *(tabInt + i), (i == 9 ? "\n" : ", "));
    }

    printf("Tableau de flottants (avant) : ");
    for (i = 0; i < 10; ++i)
    {
        printf("%.2f%s", *(tabFloat + i), (i == 9 ? "\n" : ", "));
    }

    pInt = tabInt;
    pFloat = tabFloat;
    for (i = 0; i < 10; ++i, ++pInt, ++pFloat)
    {
        if (i % 2 == 0)
        {
            *pInt *= 3;
            *pFloat *= 3.0f;
        }
    }

    printf("Tableau d'entiers (apres) : ");
    for (i = 0; i < 10; ++i)
    {
        printf("%d%s", *(tabInt + i), (i == 9 ? "\n" : ", "));
    }

    printf("Tableau de flottants (apres) : ");
    for (i = 0; i < 10; ++i)
    {
        printf("%.2f%s", *(tabFloat + i), (i == 9 ? "\n" : ", "));
    }

    return 0;
}
