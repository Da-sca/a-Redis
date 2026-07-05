#include <stdlib.h>
#include <string.h>
#include "value.h"

// Modifie leur fonction pour initialiser le TYPE_STRING
Value value_create_string(const char* str) {
    Value v;
    v.type = TYPE_STRING;
    v.data.str_value = strdup(str);
    return v;
}

// Ajoute la fonction pour initialiser une liste double vide
Value value_create_list() {
    Value v;
    v.type = TYPE_LIST;
    v.data.list_value = (ListeDouble*)malloc(sizeof(ListeDouble));
    if (v.data.list_value != NULL) {
        v.data.list_value->tete = NULL;
        v.data.list_value->queue = NULL;
    }
    return v;
}

// Ton implémentation de LPUSH (Insertion en tête en O(1))
void value_list_lpush(Value* value, const char* str) {
    if (value == NULL || value->type != TYPE_LIST || str == NULL) return;
    
    ListeDouble* l = value->data.list_value;
    CelluleListe* nouvelle = (CelluleListe*)malloc(sizeof(CelluleListe));
    if (nouvelle == NULL) return;
    
    nouvelle->valeur = strdup(str);
    nouvelle->prec = NULL;
    nouvelle->suiv = l->tete;

    if (l->tete == NULL) {
        l->queue = nouvelle;
    } else {
        l->tete->prec = nouvelle;
    }
    l->tete = nouvelle;
}

// Ton implémentation de RPUSH (Insertion en queue en O(1))
void value_list_rpush(Value* value, const char* str) {
    if (value == NULL || value->type != TYPE_LIST || str == NULL) return;
    
    ListeDouble* l = value->data.list_value;
    CelluleListe* nouvelle = (CelluleListe*)malloc(sizeof(CelluleListe));
    if (nouvelle == NULL) return;
    
    nouvelle->valeur = strdup(str);
    nouvelle->suiv = NULL;
    nouvelle->prec = l->queue;

    if (l->queue == NULL) {
        l->tete = nouvelle;
    } else {
        l->queue->suiv = nouvelle;
    }
    l->queue = nouvelle;
}

// Nettoyage intelligent et sécurisé de la mémoire selon le type stocké
void value_free(Value* value) {
    if (value == NULL) return;

    if (value->type == TYPE_STRING) {
        if (value->data.str_value != NULL) {
            free(value->data.str_value);
            value->data.str_value = NULL;
        }
    } 
    else if (value->type == TYPE_LIST) {
        if (value->data.list_value != NULL) {
            CelluleListe* curr = value->data.list_value->tete;
            while (curr != NULL) {
                CelluleListe* suivant = curr->suiv;
                free(curr->valeur);
                free(curr);
                curr = suivant;
            }
            free(value->data.list_value);
            value->data.list_value = NULL;
        }
    }
}
