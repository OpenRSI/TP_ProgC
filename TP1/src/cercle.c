#include <stdio.h>

int main(void)
{
    const double pi = 3.14159;
    double rayon = 6.0;

    /* Calcule l'aire et le perimetre a partir du rayon. */
    double aire = pi * rayon * rayon;
    double perimetre = 2 * pi * rayon;

    printf("Rayon : %.2f\n", rayon);
    printf("Aire : %.2f\n", aire);
    printf("Perimetre : %.2f\n", perimetre);

    return 0;
}
