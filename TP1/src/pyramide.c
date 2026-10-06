#include <stdio.h>

int main() {
    // Déclaration et initialisation de la hauteur de la pyramide
    int n = 5; 
    int i, j;

    // Boucle externe : itère sur chaque niveau (de 1 à n)
    for (i = 1; i <= n; i++) {
        
        // 1. Boucle pour afficher les espaces nécessaires au centrage
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // 2. Boucle pour afficher les nombres croissants (de 1 à i)
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        // 3. Boucle pour afficher les nombres décroissants (de i-1 à 1)
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }

        // Passage à la ligne suivante après chaque niveau
        printf("\n");
    }

    // Message final indiquant la fin de la génération
    printf("Génération de la pyramide terminée !\n");

    return 0;
}