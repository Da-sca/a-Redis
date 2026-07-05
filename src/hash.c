#include <stddef.h>
//iMPLEMENTAION BASIC POUR TESTER LE TABLEAU A MODIFIER
// algo djb2
size_t hash_function(const char* key) {
    size_t hash = 5381;
    while (*key) {
        hash = hash * 33 + (unsigned char)(*key);
        key++;
    }
    return hash;
}
