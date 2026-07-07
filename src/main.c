#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "engine.h"

int main(void) {
    HashTable* ht = ht_create(5);
    
    char buffer[1024];
    printf("Bienvenue dans a-Redis. Commandes : SET <key> <val>, GET <key>, DEL <key>, EXIT\n");

    while (1) {
        printf("> ");
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        
        // Nettoyage de la saisie
        buffer[strcspn(buffer, "\n")] = 0;

        // Découpage en jetons
        char* cmd = strtok(buffer, " ");
        if (!cmd) continue;

        if (strcmp(cmd, "EXIT") == 0) {
            break;
        } 
        else if (strcmp(cmd, "SET") == 0) {
            char* key = strtok(NULL, " ");
            char* val = strtok(NULL, " ");
            if (key && val) {
                cmd_set(ht, key, val);
            } else {
                printf("Usage: SET <key> <value>\n");
            }
        } 
        else if (strcmp(cmd, "GET") == 0) {
            char* key = strtok(NULL, " ");
            if (key) {
                cmd_get(ht, key);
            } else {
                printf("Usage: GET <key>\n");
            }
        } 
        else if (strcmp(cmd, "DEL") == 0) {
            char* key = strtok(NULL, " ");
            if (key) {
                cmd_del(ht, key);
            } else {
                printf("Usage: DEL <key>\n");
            }
        } 
        else {
            printf("Commande inconnue : %s\n", cmd);
        }
    }

    ht_destroy(ht);
    printf("Arrêt du moteur.\n");
    
    return 0;
}