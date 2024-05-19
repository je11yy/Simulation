#include "HashSet.h"

int hash_function(int key, size_t size)
{
    return key % size;
}

status HS_set_null(Hash_Set_ptr set)
{
    set->size = 3;
    set->max_chain_size = 0;
    set->min_chain_size = 0;
    set->elements = NULL;
    return success;
}

HS_element_ptr HS_element_create(int key, Department_ptr department)
{
    HS_element_ptr element = (HS_element_ptr)malloc(sizeof(HS_element));
    if (!element) return NULL;
    element->department = department;
    element->next_elements_count = 0;
    element->next = NULL;
    element->key = key;
    return element;
}

void HS_element_free(HS_element_ptr element)
{
    if (!element) return;
    HS_element_free(element->next);
    department_free(element->department);
    element->next = NULL;
    free(element);
    element = NULL;
}

HS_element_array HS_element_array_create(size_t size)
{
    HS_element_array array = (HS_element_array)calloc(size, sizeof(HS_element_ptr));
    if (!array) return NULL;
    return array;
}

status HS_element_array_realloc(HS_element_array * array, size_t old_size, size_t new_size)
{
    HS_element_array tmp = (HS_element_array)realloc(*array, new_size * sizeof(HS_element_ptr));
    if (!tmp)
    {
        HS_element_array_free(*array, old_size);
        return no_memory;
    }
    *array = tmp;
    return success;
}

void HS_element_array_free(HS_element_array array, size_t size)
{
    if (!array) return;
    for (size_t i = 0; i < size; ++i) HS_element_free(array[i]);
    free(array);
    array = NULL;
}

size_t calculate_next_prime_number(size_t size)
{
    while(1)
    {
        size_t c = 1;
        size++;
        for (size_t i = 2; i <= size; ++i) if (size % i == 0) c++;
        if (c == 2) return size;
    }
}

Hash_Set_ptr HS_create()
{
    Hash_Set_ptr set = (Hash_Set_ptr)malloc(sizeof(Hash_Set));
    if (!set) return NULL;
    set->size = 3;
    set->max_chain_size = 0;
    set->min_chain_size = 0;
    set->elements = HS_element_array_create(set->size);
    if (!set->elements)
    {
        free(set);
        return NULL;
    }
    return set;
}

void HS_free(Hash_Set_ptr set)
{
    if (!set) return;
    HS_element_array_free(set->elements, set->size);
    free(set);
    set = NULL;
}

status HS_insert(Hash_Set_ptr set, int key, Department_ptr department)
{
    if (!set || !department) return invalid_function_argument;

    HS_element_ptr element = HS_element_create(key, department);
    if (!element) return no_memory;

    int index = hash_function(key, set->size);
    element->next = set->elements[index];
    set->elements[index] = element;
    if (element->next) element->next_elements_count = element->next->next_elements_count;
    if (set->max_chain_size < element->next_elements_count) set->max_chain_size = element->next_elements_count;
    if (set->min_chain_size > element->next_elements_count) set->max_chain_size = element->next_elements_count;

    if (set->max_chain_size > 2 * (set->min_chain_size ? set->min_chain_size : 1)) return HS_rebuild(set);
    return success;
}

void decrease_chain_size(HS_element_ptr from, HS_element_ptr to)
{
    HS_element_ptr current = from;
    while (current != to)
    {
        current->next_elements_count--;
        current = current->next;
    }
}

status HS_rebuild(Hash_Set_ptr set)
{
    size_t prev_size = set->size;
    set->size = calculate_next_prime_number(set->size);
    status error = HS_element_array_realloc(&set->elements, prev_size, set->size);
    if (error != success) return error;
    if (!set->elements) return no_memory;

    for (size_t i = 0; i < prev_size; ++i)
    {
        HS_element_ptr current = set->elements[i];
        HS_element_ptr prev = NULL;
        HS_element_ptr first = current;
        while (current)
        {
            HS_element_ptr next = current->next;

            int index = hash_function(current->key, set->size);
            if (index == i) continue;

            if (prev)
            {
                prev->next = next;
                decrease_chain_size(first, next);
            }

            current->next = set->elements[index];
            set->elements[index] = current;

            if (current->next) current->next_elements_count = current->next->next_elements_count;
            else current->next_elements_count = 0;

            if (set->max_chain_size < current->next_elements_count) set->max_chain_size = current->next_elements_count;
            if (set->min_chain_size > current->next_elements_count) set->max_chain_size = current->next_elements_count;
        }
    }

    if (set->max_chain_size > 2 * (set->min_chain_size ? set->min_chain_size : 1)) return HS_rebuild(set);
}

status HS_find(Hash_Set_ptr set, int key, Department_ptr * result)
{
    if (!set) return invalid_function_argument;
    int index = hash_function(key, set->size);

    HS_element_ptr current = set->elements[index];
    while (current && current->key != key) current = current->next;
    if (!current) return cannot_find;
    *result = current->department;
    return success;
}