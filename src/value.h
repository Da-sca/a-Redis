#ifndef VALUE_H
#define VALUE_H
//Double linked list will be implemented here later as a possible value type

typedef struct {
    char* str_value;
} Value;

Value value_create_string(const char* str);

void value_free(Value* value);

#endif
