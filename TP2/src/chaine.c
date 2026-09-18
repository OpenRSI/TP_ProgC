#include <stdio.h>

int longueur(const char *chaine)
{
    int i = 0;
    while (chaine[i] != '\0')
    {
        ++i;
    }
    return i;
}

void copier(char *destination, const char *source)
{
    int i = 0;
    while ((destination[i] = source[i]) != '\0')
    {
        ++i;
    }
}

void concatener(char *destination, const char *source)
{
    int i = 0;
    int j = 0;

    while (destination[i] != '\0')
    {
        ++i;
    }

    while ((destination[i] = source[j]) != '\0')
    {
        ++i;
        ++j;
    }
}

int main(void)
{
    char chaine1[100] = "Hello";
    char chaine2[100] = " World!";
    char copie[100];
    char concat[100];

    printf("Longueur de \"%s\" : %d\n", chaine1, longueur(chaine1));

    copier(copie, chaine1);
    printf("Copie : %s\n", copie);

    copier(concat, chaine1);
    concatener(concat, chaine2);
    printf("Concatenation : %s\n", concat);

    return 0;
}
