#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_

#include "../../application.h"

typedef struct FH_node
{
    Application_ptr application;
    size_t rank;

    struct FH_node * child;
    struct FH_node * left;
    struct FH_node * right;

} FH_node, *FH_node_ptr;

typedef struct Fibonacci_Heap
{
    FH_node_ptr max;
    size_t size;

} Fibonacci_Heap, *Fibonacci_Heap_ptr;

Fibonacci_Heap_ptr Fibonacci_Heap_create();
void Fibonacci_Heap_free(Fibonacci_Heap_ptr * storage);
status Fibonacci_Heap_copy(Fibonacci_Heap_ptr * to, Fibonacci_Heap_ptr from);

FH_node_ptr Fibonacci_Heap_node_create(Application_ptr application);
void Fibonacci_Heap_node_free(FH_node_ptr node);
status Fibonacci_Heap_node_copy(FH_node_ptr * to, FH_node_ptr from);

status Fibonacci_Heap_meld(Fibonacci_Heap_ptr * res, Fibonacci_Heap_ptr * first, Fibonacci_Heap_ptr * second);
status Fibonacci_Heap_merge(Fibonacci_Heap_ptr * res, Fibonacci_Heap_ptr * first, Fibonacci_Heap_ptr * second);

status Fibonacci_Heap_get_max(Fibonacci_Heap_ptr * storage, Application_ptr * res_application);
status Fibonacci_Heap_delete_max(Fibonacci_Heap_ptr * storage, Application_ptr * res_application);

status Fibonacci_Heap_insert(Fibonacci_Heap_ptr * storage, Application_ptr application);
status Fibonacci_Heap_set_null(Fibonacci_Heap_ptr heap);


#endif