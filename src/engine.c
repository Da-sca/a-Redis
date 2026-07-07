#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void resize(HashTable* ht) {
    int old_size = ht->size;
    Node** old_array = ht->array;

    ht->size = old_size * 2;
    ht->array = (Node**)calloc(ht->size, sizeof(Node*));
    ht->count = 0; // Réinitialisation pour recompter lors de la réinsertion

    for (int i = 0; i < old_size; i++) {
        Node* current = old_array[i];
        while (current != NULL) {
            Node* next = current->next;
            
            // Recalcul de l'index avec la nouvelle taille
            unsigned int new_index = hash_function(current->key) % ht->size;
            
            // Insertion en tête dans le nouveau tableau
            current->next = ht->array[new_index];
            ht->array[new_index] = current;
            ht->count++;
            
            current = next;
        }
    }
    free(old_array);
}

void cmd_set(HashTable* ht, const char* key, const char* value) {
    // Redimensionnement automatique si > 75%
    if ((float)(ht->count + 1) / ht->size > 0.75) {
        resize(ht);
    }

    unsigned int index = hash_function(key) % ht->size;
    Node* current = ht->array[index];

    // Mise à jour si la clé existe
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }

    // Insertion en tête (O(1))
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->array[index];
    ht->array[index] = new_node;
    ht->count++;
    printf("OK\n");
}

void cmd_get(HashTable* ht, const char* key) {
    unsigned int index = hash_function(key) % ht->size;
    Node* current = ht->array[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf("%s\n", current->value);
            return;
        }
        current = current->next;
    }
    printf("(nil)\n");
}

void cmd_del(HashTable* ht, const char* key) {
    unsigned int index = hash_function(key) % ht->size;
    Node* current = ht->array[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) ht->array[index] = current->next;
            else prev->next = current->next;
            
            free(current->key);
            free(current->value);
            free(current);
            ht->count--;
            printf("OK\n");
            return;
        }
        prev = current;
        current = current->next;
    }
}