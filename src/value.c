#include <stdlib.h>
#include <string.h>
#include "value.h"

// Initialise une Value de type STRING
Value value_create_string(const char* str) {
    Value v;
    v.type = TYPE_STRING;
    v.data.str_value = strdup(str);
    return v;
}

// Initialise une Value de type LIST (liste doublement chaînée vide)
Value value_create_list(void) {
    Value v;
    v.type = TYPE_LIST;
    v.data.list_value = (ListeDouble*)malloc(sizeof(ListeDouble));
    if (v.data.list_value != NULL) {
        v.data.list_value->tete = NULL;
        v.data.list_value->queue = NULL;
        v.data.list_value->taille = 0;
    }
    return v;
}

// Vérifications de type — utiles pour engine.c
int value_is_string(const Value* value) {
    return value != NULL && value->type == TYPE_STRING;
}

int value_is_list(const Value* value) {
    return value != NULL && value->type == TYPE_LIST;
}

// LPUSH — insertion en tête, O(1)
void value_list_lpush(Value* value, const char* str) {
    if (!value_is_list(value)) return;
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
    l->taille++;
}
// RPUSH — insertion en queue, O(1)
void value_list_rpush(Value* value, const char* str) {
    if (value_is_list(value)) return;

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
    l->taille++;
}

// LPOP — extraction en tête, O(1). Retourne NULL si liste vide ou mauvais type.
char* value_list_lpop(Value* value) {
    if (!value_is_list(value)) return NULL;

    ListeDouble* l = value->data.list_value;
    if (l->tete == NULL) return NULL;   // liste vide

    CelluleListe* ancienne_tete = l->tete;
    char* resultat = ancienne_tete->valeur;   // on récupère le pointeur, PAS de free ici

    l->tete = ancienne_tete->suiv;
    if (l->tete != NULL) {
        l->tete->prec = NULL;
    } else {
        l->queue = NULL;   // la liste devient vide
    }

    free(ancienne_tete);    // on libère seulement la cellule, pas la string qu'elle contenait
    l->taille--;
    return resultat;         // l'appelant récupère la string et devra la free() lui-même
}

// RPOP — extraction en queue, O(1). Retourne NULL si liste vide ou mauvais type.
char* value_list_rpop(Value* value) {
    if (!value_is_list(value)) return NULL;

    ListeDouble* l = value->data.list_value;
    if (l->queue == NULL) return NULL;   // liste vide

    CelluleListe* ancienne_queue = l->queue;
    char* resultat = ancienne_queue->valeur;

    l->queue = ancienne_queue->prec;
    if (l->queue != NULL) {
        l->queue->suiv = NULL;
    } else {
        l->tete = NULL;   // la liste devient vide
    }

    free(ancienne_queue);
    l->taille--;
    return resultat;
}

// Nettoyage complet selon le type stocké
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
