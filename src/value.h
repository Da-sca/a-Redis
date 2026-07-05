#ifndef VALUE_H
#define VALUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- TES STRUCTURES : La liste doublement chaînée ---
typedef struct CelluleListe {
    char* valeur;
    struct CelluleListe* prec;
    struct CelluleListe* suiv;
} CelluleListe;

typedef struct {
    CelluleListe* tete;
    CelluleListe* queue;
} ListeDouble;

// --- L'ÉNUMÉRATION : Pour que le dictionnaire sache ce que contient la clé ---
typedef enum {
    TYPE_STRING,
    TYPE_LIST
} ValueType;

// --- LA STRUCTURE GLOBALE COMPLÉTÉE AVEC TON UNION ---
typedef struct {
    ValueType type; 
    union {
        char* str_value;          // Code initial de tes camarades
        ListeDouble* list_value;  // Ton ajout pour la liste double
    } data;
} Value;

// --- LES PROTOTYPES DES FONCTIONS ---
Value value_create_string(const char* str);
Value value_create_list(); 
void value_free(Value* value);

// Tes fonctions métiers pour l'API (LPUSH et RPUSH en O(1))
void value_list_lpush(Value* value, const char* str);
void value_list_rpush(Value* value, const char* str);

#endif
