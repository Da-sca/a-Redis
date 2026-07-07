#ifndef ENGINE_H
#define ENGINE_H

#include "hashtable.h"

// Commandes sur les strings
void cmd_set(HashTable* ht, const char* key, const char* value);
void cmd_get(HashTable* ht, const char* key);
void cmd_del(HashTable* ht, const char* key);
void cmd_lpush(HashTable* ht, const char* key, const char* value);
void cmd_rpush(HashTable* ht, const char* key, const char* value);
void cmd_lpop(HashTable* ht, const char* key);
void cmd_rpop(HashTable* ht, const char* key);
void error_message(void);
#endif
