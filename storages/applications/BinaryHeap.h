#ifndef _BINARY_HEAP_H
#define _BINARY_HEAP_H

#include "../../application.h"

typedef struct Binary_Heap
{
    size_t size;
    size_t capacity;
    Application_ptr * elements;
} Binary_Heap, *Binary_Heap_ptr;

void Binary_Heap_free(Binary_Heap_ptr * storage);
Binary_Heap_ptr Binary_Heap_create();

status Binary_Heap_merge(Binary_Heap_ptr * res, Binary_Heap_ptr * first, Binary_Heap_ptr * second);
status Binary_Heap_meld(Binary_Heap_ptr * res, Binary_Heap_ptr * first, Binary_Heap_ptr * second);

status Binary_Heap_get_max(Binary_Heap_ptr * storage, Application_ptr * res_application);
status Binary_Heap_delete_max(Binary_Heap_ptr * storage, Application_ptr * res_application);

status Binary_Heap_insert(Binary_Heap_ptr * storage, Application_ptr application);

status Binary_Heap_sift_down(Binary_Heap_ptr * storage, size_t i);
status Binary_Heap_sift_up(Binary_Heap_ptr * storage);
status Binary_Heap_set_null(Binary_Heap_ptr heap);

#endif