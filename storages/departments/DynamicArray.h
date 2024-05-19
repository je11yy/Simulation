#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

#include "department.h"

typedef struct Dynamic_Array_element
{
    int key;
    Department_ptr department;

} Dynamic_Array_element, *Dynamic_Array_element_ptr, **Dynamic_Array_element_array;

typedef struct Dynamic_Array
{
    Dynamic_Array_element_array array;
    size_t size;
    size_t capacity;
} Dynamic_Array, *Dynamic_Array_ptr;

Dynamic_Array_element_ptr dynamic_array_element_create(int key, Department_ptr department);
void dynamic_array_element_free(Dynamic_Array_element_ptr element);

Dynamic_Array_element_array dynamic_array_element_array_create(size_t size);
status dynamic_array_element_array_realloc(Dynamic_Array_element_array * array, size_t size);
void dynamic_array_element_array_free(Dynamic_Array_element_array array, size_t size);

Dynamic_Array_ptr dynamic_array_create();
void dynamic_array_free(Dynamic_Array_ptr array);

status dynamic_array_insert(Dynamic_Array_ptr array, int key, Department_ptr department);
status dynamic_array_find(Dynamic_Array_ptr array, int key, Department_ptr * result);
status dynamic_array_set_null(Dynamic_Array_ptr array);

#endif