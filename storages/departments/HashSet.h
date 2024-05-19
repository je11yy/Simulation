#ifndef _HASH_SET_H
#define _HASH_SET_H

#include "department.h"

typedef struct HS_element
{
    int key;
    Department_ptr department;
    struct HS_element * next;
    size_t next_elements_count;

} HS_element, *HS_element_ptr, **HS_element_array;

typedef struct Hash_Set
{
    size_t size;
    HS_element_array elements;
    size_t max_chain_size;
    size_t min_chain_size;

} Hash_Set, *Hash_Set_ptr;

int hash_function(int key, size_t size);
size_t calculate_next_prime_number(size_t size);

void decrease_chain_size(HS_element_ptr from, HS_element_ptr to);

HS_element_ptr HS_element_create(int key, Department_ptr department);
void HS_element_free(HS_element_ptr element);

HS_element_array HS_element_array_create(size_t size);
status HS_element_array_realloc(HS_element_array * array, size_t old_size, size_t new_size);
void HS_element_array_free(HS_element_array array, size_t size);

Hash_Set_ptr HS_create();
void HS_free(Hash_Set_ptr set);

status HS_insert(Hash_Set_ptr set, int key, Department_ptr department);
status HS_rebuild(Hash_Set_ptr set);
status HS_find(Hash_Set_ptr set, int key, Department_ptr * result);
status HS_set_null(Hash_Set_ptr set);

#endif