#include <stdio.h>

int longueurChaine(const char *chaine)
{
    int taille = 0;
    while (chaine[taille] != '\0')
    {
        ++taille;
    }
    return taille;
}

int comparerChaines(const char *a, const char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return 0;
        }
        ++i;
    }
    return a[i] == '\0' && b[i] == '\0';
}

int main(void)
{
    const char *phrases[10] = {
        "Bonjour, comment ca va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };

    char phraseRecherchee[200];
    int i;
    int trouve = 0;

    printf("Entrez la phrase a rechercher : ");
    fgets(phraseRecherchee, sizeof(phraseRecherchee), stdin);

    /* supprime le saut de ligne final si present */
    for (i = 0; phraseRecherchee[i] != '\0'; ++i)
    {
        if (phraseRecherchee[i] == '\n')
        {
            phraseRecherchee[i] = '\0';
            break;
        }
    }

    for (i = 0; i < 10; ++i)
    {
        if (comparerChaines(phraseRecherchee, phrases[i]))
        {
            trouve = 1;
            break;
        }
    }

    if (trouve)
    {
        printf("Phrase trouvee\n");
    }
    else
    {
        printf("Phrase non trouvee\n");
    }

    return 0;
}
