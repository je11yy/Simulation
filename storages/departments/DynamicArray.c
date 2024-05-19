#include "DynamicArray.h"

Dynamic_Array_element_ptr dynamic_array_element_create(int key, Department_ptr department)
{
    Dynamic_Array_element_ptr element = (Dynamic_Array_element_ptr)malloc(sizeof(Dynamic_Array_element));
    if (!element) return NULL;
    element->key = key;
    element->department = department;
    return element;
}

Dynamic_Array_element_array dynamic_array_element_array_create(size_t size)
{
    Dynamic_Array_element_array array = (Dynamic_Array_element_array)calloc(size, sizeof(Dynamic_Array_element_ptr));
    if (!array) return NULL;
    return array;
}

status dynamic_array_element_array_realloc(Dynamic_Array_element_array * array, size_t size)
{
    if (!*array) return invalid_function_argument;

    Dynamic_Array_element_array tmp = (Dynamic_Array_element_array)realloc(*array, sizeof(Dynamic_Array_element_ptr) * size);
    if (!tmp) return no_memory;
    *array = tmp;
    return success;
}

void dynamic_array_element_free(Dynamic_Array_element_ptr element)
{
    if (!element) return;
    department_free(element->department);
    free(element);
    element = NULL;
}

void dynamic_array_element_array_free(Dynamic_Array_element_array array, size_t size)
{
    for (size_t i = 0; i < size; ++i) dynamic_array_element_free(array[i]);
    free(array);
    array = NULL;
}

status dynamic_array_set_null(Dynamic_Array_ptr array)
{
    array->size = 0;
    array->capacity = 4;

    array->array = NULL;
    return success;
}

Dynamic_Array_ptr dynamic_array_create()
{
    Dynamic_Array_ptr array = (Dynamic_Array_ptr)malloc(sizeof(Dynamic_Array));
    if (!array) return NULL;
    array->size = 0;
    array->capacity = 4;

    array->array = dynamic_array_element_array_create(array->capacity);
    if (!array->array)
    {
        free(array);
        return NULL;
    }
    return array;
}

void dynamic_array_free(Dynamic_Array_ptr array)
{
    dynamic_array_element_array_free(array->array, array->size);
    free(array);
    array = NULL;
}

status dynamic_array_insert(Dynamic_Array_ptr array, int key, Department_ptr department)
{
    Dynamic_Array_element_ptr new_element = dynamic_array_element_create(key, department);
    if (!new_element) return no_memory;
    if (array->size == array->capacity)
    {
        array->capacity *= 2;
        status error = dynamic_array_element_array_realloc(&array->array, array->capacity);
        if (error != success) return no_memory;
    }

    int index = -1;
    for (size_t i = 0; i < array->size; ++i)
    {
        if (array->array[i]->key > key)
        {
            index = i;
            break;
        }
    }

    if (index < 0) index = array->size;
    else
    {
        size_t tmp = array->size + 1;
        while (tmp != index)
        {
            array->array[tmp] = array->array[tmp - 1];
            tmp--;
        }
    }

    array->array[index] = new_element;
    array->size++;

    return success;
}

status dynamic_array_find(Dynamic_Array_ptr array, int key, Department_ptr * result)
{
    if (!array || !array->array) return invalid_function_argument;

    int left = 0;
    int right = array->size - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        if (array->array[middle]->key == key)
        {
            *result = array->array[middle]->department;
            return success;
        }
        else if (array->array[middle]->key > key) right = middle - 1;
        else left = middle + 1;
    }

    if (array->array[1]->key == key)
    {
        *result = array->array[1]->department;
        return success;
    }

    *result = NULL;
    return cannot_find;
}