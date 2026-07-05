#include "collision.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>

/*
 * find_in_bucket : cherche un maillon dont la cle correspond exactement
 * a `key`, en parcourant la liste chainee a partir de `bucket_head`.
 *
 * Retourne le Node* trouve, ou NULL si la cle n'existe pas dans ce bucket.
 */
Node* find_in_bucket(Node* bucket_head, const char* key) {
    Node* current = bucket_head;

    while (current != NULL) {
        // strcmp renvoie 0 si les deux chaines sont identiques
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }

    // Parcouru toute la liste, cle non trouvee
    return NULL;
}

/*
 * insert_or_update : calcule le bucket via le hash, puis :
 * - si la cle existe deja -> met a jour la valeur
 * - sinon -> cree un nouveau maillon en tete de la liste chainee
 */
void insert_or_update(HashTable* ht, const char* key, Value value) {
    // 1. Calculer l'index du bucket a partir du hash
    size_t index = hash_function(key) % ht->capacity;

    // 2. Recuperer la tete de la liste chainee de ce bucket
    Node* bucket_head = ht_get_bucket(ht, index);

    // 3. Verifier si la cle existe deja
    Node* existing = find_in_bucket(bucket_head, key);

    if (existing != NULL) {
        // La cle existe : on libere l'ancienne valeur et on met la nouvelle
        value_free(&existing->value);
        existing->value = value;
        return;
    }

    // 4. La cle n'existe pas : on cree un nouveau maillon
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return; // echec d'allocation memoire
    }

    // On duplique la cle (strdup copie la chaine dans un nouvel espace memoire)
    new_node->key = strdup(key);
    new_node->value = value;

    // On insere le nouveau maillon EN TETE de la liste (le plus simple/rapide, O(1))
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;

    // 5. Mettre a jour le compteur d'elements
    ht->count++;

    // 6. Verifier si la table a besoin d'etre agrandie
    if (needs_resize(ht)) {
        ht_resize(ht);
    }
}

/*
 * delete_from_bucket : cherche la cle, et si trouvee, retire son maillon
 * de la liste chainee en reliant les maillons voisins entre eux.
 *
 * Retourne 1 si la suppression a reussi, 0 si la cle n'existait pas.
 */
int delete_from_bucket(HashTable* ht, const char* key) {
    size_t index = hash_function(key) % ht->capacity;

    Node* current = ht->buckets[index];
    Node* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Cle trouvee : on retire ce maillon de la chaine

            if (previous == NULL) {
                // Le maillon a supprimer est le premier de la liste
                ht->buckets[index] = current->next;
            } else {
                // On "saute" par-dessus le maillon a supprimer
                previous->next = current->next;
            }

            node_free(current); // libere key, value, et le node lui-meme
            ht->count--;
            return 1; // succes
        }

        previous = current;
        current = current->next;
    }

    return 0; // cle non trouvee
}
