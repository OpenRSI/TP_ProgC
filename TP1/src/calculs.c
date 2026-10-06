#include <stdio.h>

int main(void)
{
    int num1 = 16;
    int num2 = 3;
    char op = '+';
    int resultat;

    /* switch choisit l'operation ; break termine le case choisi. */
    switch (op) {
        case '+':
            resultat = num1 + num2;
            break;
        case '-':
            resultat = num1 - num2;
            break;
        case '*':
            resultat = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printf("Erreur : division par zero.\n");
                return 1;
            }
            resultat = num1 / num2;
            break;
        case '%':
            if (num2 == 0) {
                printf("Erreur : modulo par zero.\n");
                return 1;
            }
            resultat = num1 % num2;
            break;
        case '&':
            resultat = num1 & num2;
            break;
        case '|':
            resultat = num1 | num2;
            break;
        case '~':
            /* Le complement ~ agit uniquement sur num1. */
            resultat = ~num1;
            break;
        default:
            printf("Erreur : operateur inconnu.\n");
            return 1;
    }

    if (op == '~') {
        printf("~%d = %d\n", num1, resultat);
    } else {
        printf("%d %c %d = %d\n", num1, op, num2, resultat);
    }

    return 0;
}
