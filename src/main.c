#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hash.h"

int main(void) {
    HashTable* ht = ht_create(5);   // on met 4 pour forcer le reszi

    for (int i = 0; i < 5; i++) {
        char key[20];
        sprintf(key, "key%d", i);

        Node* n = malloc(sizeof(Node));
        n->key = strdup(key);
        n->value = value_create_string("test");
        n->next = NULL;

        size_t index = hash_function(n->key) % ht->capacity;
        n->next = ht->buckets[index];
        ht->buckets[index] = n;
        ht->count++;

        if (needs_resize(ht)) {
            printf("Le resize est lancer ancienne capacite = %zu\n", ht->capacity);
            ht_resize(ht);
            printf("nouvelle capacite = %zu\n", ht->capacity);
        }
    }

    ht_destroy(ht);
    return 0;
}
