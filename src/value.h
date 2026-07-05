#ifndef VALUE_H
#define VALUE_H
//Double linked list will be implemented here later as a possible value type

typedef struct {
    char* str_value;
} Value;

Value value_create_string(const char* str);
Value value_create_list(void);
void value_list_push_back(Value* list_val, const char* str);
void value_free(Value* value); //devra prendre en compte liste et String

#endif
