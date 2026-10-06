#include "operator.h"

int somme(int num1, int num2) { return num1 + num2; }
int difference(int num1, int num2) { return num1 - num2; }
int produit(int num1, int num2) { return num1 * num2; }
int quotient(int num1, int num2) { return num1 / num2; }
int modulo(int num1, int num2) { return num1 % num2; }
int et(int num1, int num2) { return num1 & num2; }
int ou(int num1, int num2) { return num1 | num2; }
int negation(int num) { return ~num; }

int calculer(int num1, int num2, char op)
{
    switch (op)
    {
        case '+': return somme(num1, num2);
        case '-': return difference(num1, num2);
        case '*': return produit(num1, num2);
        case '/': return quotient(num1, num2);
        case '%': return modulo(num1, num2);
        case '&': return et(num1, num2);
        case '|': return ou(num1, num2);
        case '~': return negation(num1);
        default:
            return 0;
    }
}
