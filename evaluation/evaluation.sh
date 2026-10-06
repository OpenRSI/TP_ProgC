#!/usr/bin/env bash

set -u

root_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
read -r -a compiler <<< "${CC:-gcc}"
errors=0

if ((${#compiler[@]} == 0)) || ! command -v "${compiler[0]}" >/dev/null 2>&1; then
  printf 'Erreur : compilateur C introuvable (%s).\n' "${CC:-gcc}" >&2
  exit 2
fi

printf '%s\n' '============================================================'
printf '%s\n' '                 Evaluation des travaux pratiques'
printf '%s\n' '============================================================'
printf 'Compilateur : %s\n' "${compiler[*]}"

for number in {1..6}; do
  practical="TP${number}"
  practical_dir="$root_dir/$practical"
  source_dir="$practical_dir/src"
  documentation="$practical_dir/TP${number}.md"
  practical_errors=0

  printf '\n%s\n' "[$practical]"

  if [[ -s "$documentation" ]]; then
    printf '  OK  Documentation presente\n'
  else
    printf '  ECHEC Documentation absente ou vide : %s\n' "$documentation"
    practical_errors=$((practical_errors + 1))
  fi

  if [[ ! -d "$source_dir" ]]; then
    printf '  ECHEC Dossier source absent : %s\n' "$source_dir"
    practical_errors=$((practical_errors + 1))
  else
    sources=("$source_dir"/*.c)
    if [[ ! -e "${sources[0]}" ]]; then
      printf '  ECHEC Aucun fichier C dans %s\n' "$source_dir"
      practical_errors=$((practical_errors + 1))
    else
      for source in "${sources[@]}"; do
        if [[ ! -s "$source" ]]; then
          printf '  ECHEC Fichier C absent ou vide : %s\n' "${source#"$root_dir"/}"
          practical_errors=$((practical_errors + 1))
          continue
        fi

        printf '  C   %s ... ' "${source#"$root_dir"/}"
        if output=$("${compiler[@]}" -std=c11 -Wall -Wextra -Wpedantic -Werror \
          -fsyntax-only "$source" 2>&1); then
          printf '%s\n' 'OK'
        else
          printf '%s\n' 'ECHEC'
          printf '%s\n' "$output" | sed 's/^/      /'
          practical_errors=$((practical_errors + 1))
        fi
      done
    fi
  fi

  if ((practical_errors == 0)); then
    printf '  Resultat : SUCCES\n'
  else
    printf '  Resultat : ECHEC (%d probleme(s))\n' "$practical_errors"
    errors=$((errors + practical_errors))
  fi
done

printf '\n%s\n' '============================================================'
if ((errors == 0)); then
  printf '%s\n' 'Evaluation terminee : tous les controles ont reussi.'
else
  printf 'Evaluation terminee : %d probleme(s) detecte(s).\n' "$errors"
fi
printf '%s\n' '============================================================'

((errors == 0))
