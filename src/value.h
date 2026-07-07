#ifndef VALUE_H
#define VALUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- La liste doublement chaînée ---
typedef struct CelluleListe {
    char* valeur;
    struct CelluleListe* prec;
    struct CelluleListe* suiv;
} CelluleListe;

typedef struct {
    CelluleListe* tete;
    CelluleListe* queue;
    size_t taille;
} ListeDouble;

typedef enum {
    TYPE_STRING,
    TYPE_LIST
} ValueType;

// --- Structure globale avec union ---
typedef struct {
    ValueType type;
    union {
        char* str_value;
        ListeDouble* list_value;
    } data;
} Value;

// --- Prototypes ---
Value value_create_string(const char* str);
Value value_create_list(void);
void value_free(Value* value);

int value_is_string(const Value* value);
int value_is_list(const Value* value);

// --- Opérations sur la liste ---
void value_list_lpush(Value* value, const char* str);
void value_list_rpush(Value* value, const char* str);
char* value_list_lpop(Value* value);
char* value_list_rpop(Value* value);

#endif
