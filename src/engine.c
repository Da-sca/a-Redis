#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "collision.h"
#include "value.h"

void error_message(void) {
    printf("(error)Operation contre une cle ayant le mauvais type \n");
}

void cmd_set(HashTable* ht, const char* key, const char* value) {
    Value v = value_create_string(value);
    insert_or_update(ht, key, v);
    printf("OK\n");
}

void cmd_get(HashTable* ht, const char* key) {
    Node* found = ht_get(ht, key);

    if (found == NULL) {
        printf("(nil)\n");
        return;
    }

    if (value_is_string(&found->value)) {
        printf("%s\n", found->value.data.str_value);
    } else {
        error_message();
    }
}

void cmd_del(HashTable* ht, const char* key) {
    int success = delete_from_bucket(ht, key);
    printf(success ? "OK\n" : "(nil)\n");
}

void cmd_lpush(HashTable* ht, const char* key, const char* value) {
    Node* found = ht_get(ht, key);

    if (found == NULL) {
        // La clé n'existe pas encore → créer une nouvelle Value de type LIST
        Value v = value_create_list();
        value_list_lpush(&v, value);
        insert_or_update(ht, key, v);
        printf("(integer) 1\n");
    }
    else if (value_is_list(&found->value)) {
        value_list_lpush(&found->value, value);
        printf("(integer) %zu\n", found->value.data.list_value->taille);
    }
    else {
        error_message();
    }
}

void cmd_rpush(HashTable* ht, const char* key, const char* value) {
    Node* found = ht_get(ht, key);

    if (found == NULL) {
        Value v = value_create_list();
        value_list_rpush(&v, value);
        insert_or_update(ht, key, v);
        printf("(integer) 1\n");
    }
    else if (value_is_list(&found->value)) {
        value_list_rpush(&found->value, value);
        printf("(integer) %zu\n", found->value.data.list_value->taille);
    }
    else {
        error_message();
    }
}

void cmd_lpop(HashTable* ht, const char* key) {
    Node* found = ht_get(ht, key);

    if (found == NULL) {
        printf("(nil)\n");
        return;
    }
    if (!value_is_list(&found->value)) {
        error_message();
        return;
    }

    char* popped = value_list_lpop(&found->value);
    if (popped == NULL) {
        printf("(nil)\n");
    } else {
        printf("%s\n", popped);
        free(popped);

        // Nettoyage automatique si la liste devient vide (comportement du vrai Redis)
        if (found->value.data.list_value->taille == 0) {
            delete_from_bucket(ht, key);
        }
    }
}

void cmd_rpop(HashTable* ht, const char* key) {
    Node* found = ht_get(ht, key);

    if (found == NULL) {
        printf("(nil)\n");
        return;
    }
    if (!value_is_list(&found->value)) {
        error_message();
        return;
    }

    char* popped = value_list_rpop(&found->value);
    if (popped == NULL) {
        printf("(nil)\n");
    } else {
        printf("%s\n", popped);
        free(popped);

        if (found->value.data.list_value->taille == 0) {
            delete_from_bucket(ht, key);
        }
    }
}
