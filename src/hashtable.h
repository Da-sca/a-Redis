#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
#include "value.h"

typedef struct Node {
    char* key;
    Value value;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    size_t capacity;
    size_t count;
} HashTable;

HashTable* ht_create(size_t initial_capacity);
void ht_destroy(HashTable* ht);

int needs_resize(HashTable* ht);
void ht_resize(HashTable* ht);

Node* ht_get_bucket(HashTable* ht, size_t index);

void node_free(Node* node);

#endif
