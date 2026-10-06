#include "repertoire.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static void afficher_entrance(const char *prefix, const char *nom)
{
    printf("%s%s\n", prefix, nom);
}

static int est_repertoire(const char *chemin)
{
    struct stat info;
    if (stat(chemin, &info) != 0)
    {
        return 0;
    }
    return S_ISDIR(info.st_mode);
}

static void joindre_chemin(char *dest, size_t taille, const char *base, const char *nom)
{
    size_t base_len = strlen(base);
    size_t nom_len = strlen(nom);

    if (base_len + 1 + nom_len + 1 > taille)
    {
        return;
    }

    memcpy(dest, base, base_len);
    dest[base_len] = '/';
    memcpy(dest + base_len + 1, nom, nom_len + 1);
}

void lire_dossier(const char *nom_repertoire)
{
    DIR *rep;
    struct dirent *entree;

    rep = opendir(nom_repertoire);
    if (rep == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entree = readdir(rep)) != NULL)
    {
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
        {
            continue;
        }
        afficher_entrance("", entree->d_name);
    }

    closedir(rep);
}

void lire_dossier_recursif(const char *nom_repertoire)
{
    DIR *rep;
    struct dirent *entree;
    char chemin[4096];

    rep = opendir(nom_repertoire);
    if (rep == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entree = readdir(rep)) != NULL)
    {
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
        {
            continue;
        }

        joindre_chemin(chemin, sizeof(chemin), nom_repertoire, entree->d_name);
        afficher_entrance("", entree->d_name);

        if (est_repertoire(chemin))
        {
            lire_dossier_recursif(chemin);
        }
    }

    closedir(rep);
}

void lire_dossier_iteratif(const char *nom_repertoire)
{
    DIR *rep;
    struct dirent *entree;
    char pile[128][16384];
    int taille = 0;

    memcpy(pile[taille++], nom_repertoire, strlen(nom_repertoire) + 1);

    while (taille > 0)
    {
        char chemin_actuel[16384];
        int index = --taille;

        memcpy(chemin_actuel, pile[index], strlen(pile[index]) + 1);
        rep = opendir(chemin_actuel);
        if (rep == NULL)
        {
            perror("opendir");
            continue;
        }

        printf("Dossier : %s\n", chemin_actuel);
        while ((entree = readdir(rep)) != NULL)
        {
            char chemin_enfant[16384];

            if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
            {
                continue;
            }

            joindre_chemin(chemin_enfant, sizeof(chemin_enfant), chemin_actuel, entree->d_name);
            printf("  %s\n", entree->d_name);

            if (est_repertoire(chemin_enfant))
            {
                memcpy(pile[taille++], chemin_enfant, strlen(chemin_enfant) + 1);
            }
        }

        closedir(rep);
    }
}
