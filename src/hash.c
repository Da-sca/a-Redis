#include <stddef.h>
//iMPLEMENTAION BASIC POUR TESTER LE TABLEAU A MODIFIER
size_t hash_function(const char* key) {
    size_t hash = 0;
    while (*key) {
        hash = hash * 31 + (unsigned char)(*key);
        key++;
    }
    return hash;
}
