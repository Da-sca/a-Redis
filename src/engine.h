#ifndef ENGINE_H
#define ENGINE_H

#include "hashtable.h"

void cmd_set(HashTable* ht, const char* key, const char* value);
void cmd_get(HashTable* ht, const char* key);
void cmd_del(HashTable* ht, const char* key);
void resize(HashTable* ht);

#endif
