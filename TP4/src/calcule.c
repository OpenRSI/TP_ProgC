#include "operator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num1;
    int num2;
    char op;

    if (argc != 4)
    {
        printf("Usage: %s <operateur> <num1> <num2>\n", argv[0]);
        return 1;
    }

    op = argv[1][0];
    num1 = atoi(argv[2]);
    num2 = atoi(argv[3]);

    printf("Resultat : %d\n", calculer(num1, num2, op));
    return 0;
}
