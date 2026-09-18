#include <stdio.h>

int main(void) {
    int num1 = 16;
    int num2 = 3;
    char op = '+';

    switch (op) {
        case '+':
            printf("%d + %d = %d\n", num1, num2, num1 + num2);
            break;

        case '-':
            printf("%d - %d = %d\n", num1, num2, num1 - num2);
            break;

        case '*':
            printf("%d * %d = %d\n", num1, num2, num1 * num2);
            break;

        case '/':
            if (num2 != 0) {
                printf("%d / %d = %d\n", num1, num2, num1 / num2);
            } else {
                printf("Erreur : division par zero.\n");
            }
            break;

        case '%':
            if (num2 != 0) {
                printf("%d %% %d = %d\n", num1, num2, num1 % num2);
            } else {
                printf("Erreur : modulo par zero.\n");
            }
            break;

        case '&':
            printf("%d & %d = %d\n", num1, num2, num1 & num2);
            break;

        case '|':
            printf("%d | %d = %d\n", num1, num2, num1 | num2);
            break;

        case '~':
            printf("~%d = %d\n", num1, ~num1);
            break;

        default:
            printf("Operateur invalide.\n");
            break;
    }

    return 0;
}