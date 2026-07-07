#ifndef COLLISION_H
#define COLLISION_H

#include "hashtable.h"
#include "value.h"

Node* find_in_bucket(Node* bucket_head, const char* key);
void insert_or_update(HashTable* ht, const char* key, Value value);
int delete_from_bucket(HashTable* ht, const char* key);
Node* ht_get(HashTable* ht, const char* key);
#endif
