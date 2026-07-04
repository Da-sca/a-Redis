#include <stdlib.h>
#include "hashtable.h"
#include "hash.h"

#define LOAD_FACTOR_THRESHOLD 0.7 //Si 70% des cases sont remplies on va redimensionner

HashTable* ht_create(size_t initial_capacity) {
    HashTable* ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->capacity = initial_capacity;
    ht->count = 0;
    ht->buckets = calloc(initial_capacity, sizeof(Node*)); //calloc ici pour initialiser toutes les cases a null
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    return ht;
}

int needs_resize(HashTable* ht) {
    return ((double)ht->count / ht->capacity) > LOAD_FACTOR_THRESHOLD;
}

void ht_resize(HashTable* ht) {
    size_t old_capacity = ht->capacity;
    Node** old_buckets = ht->buckets;

    size_t new_capacity = old_capacity * 2;
    Node** new_buckets = calloc(new_capacity, sizeof(Node*));
    if (!new_buckets) return;

    for (size_t i = 0; i < old_capacity; i++) {
        Node* current = old_buckets[i];
        while (current != NULL) {
            Node* next_node = current->next;
            size_t new_index = hash_function(current->key) % new_capacity;
            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;
            current = next_node;
        }
    }

    free(old_buckets);
    ht->buckets = new_buckets;
    ht->capacity = new_capacity;
}

Node* ht_get_bucket(HashTable* ht, size_t index) {
    if (index >= ht->capacity) {
        return NULL;
    }
    return ht->buckets[index];
}

void node_free(Node* node) {
    if (node == NULL) return;
    free(node->key);
    value_free(&node->value);
    free(node);
}

void ht_destroy(HashTable* ht) {
    for (size_t i = 0; i < ht->capacity; i++) {
        Node* current = ht->buckets[i];
        while (current != NULL) {
            Node* next_node = current->next;
            node_free(current);
            current = next_node;
        }
    }
    free(ht->buckets);
    free(ht);
}
