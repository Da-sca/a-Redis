#include <stdlib.h>
#include <string.h>
#include "value.h"

Value value_create_string(const char* str) {
    Value v;
    v.str_value = strdup(str);
    return v;
}

void value_free(Value* value) {
    if (value == NULL) return;
    free(value->str_value);
    value->str_value = NULL;
}
//Double linked list will be implemented later
