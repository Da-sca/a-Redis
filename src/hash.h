#ifndef HASH_H
#define HASH_H

#include <stddef.h>  /* pour le type size_t */

/*
 * hash_function : transforme une cle texte en un numero (entier positif).
 *
 * - Entree  : une chaine de caracteres (ex: "user_name")
 * - Sortie  : un size_t (grand nombre positif), toujours le meme pour la
 *             meme cle (fonction deterministe / "fidele").
 *
 * Ce numero sera ensuite ramene dans l'intervalle des cases du tableau
 * avec un modulo (hash_function(cle) % capacity) pour choisir le bucket.
 *
 * NB : ceci n'est qu'une DECLARATION (la "carte d'identite" de la fonction).
 * La vraie recette se trouve dans hash.c.
 */
size_t hash_function(const char* key);

#endif
