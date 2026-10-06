# Evaluation des travaux pratiques

Le script `evaluation.sh` controle les six travaux pratiques :

- vérifie que la documentation `TPn/TPn.md` et le dossier `TPn/src` existent ;
- signale les dossiers source sans fichier C et les fichiers C vides ;
- compile chaque fichier `.c` en mode vérification syntaxique avec `-Wall`,
  `-Wextra`, `-Wpedantic` et `-Werror`.

Depuis n’importe quel dossier du dépôt, lancez :

```bash
./evaluation/evaluation.sh
```

Le script retourne un code différent de zéro si au moins un contrôle échoue.
GCC est utilisé par défaut ; un autre compilateur compatible peut être choisi
avec la variable d’environnement `CC`, par exemple :

```bash
CC=clang ./evaluation/evaluation.sh
```
