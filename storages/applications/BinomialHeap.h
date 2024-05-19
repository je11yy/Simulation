#ifndef _BINOMIAL_HEAP_H
#define _BINOMIAL_HEAP_H

#include "../../application.h"
#include <string.h>

#define NOT_IN_HEAP UINT_MAX

typedef struct Binomial_Heap_node
{
    Application_ptr application;
    size_t degree;

    struct Binomial_Heap_node * son;
    struct Binomial_Heap_node * brother;

} Binomial_Heap_node, *Binomial_Heap_node_ptr;

typedef struct Binomial_Heap
{
    Binomial_Heap_node * head;
    Binomial_Heap_node * max;

} Binomial_Heap, *Binomial_Heap_ptr;

void Binomial_Heap_free(Binomial_Heap_ptr * storage);
Binomial_Heap_ptr Binomial_Heap_create();
Binomial_Heap_ptr Binomial_Heap_copy(Binomial_Heap_ptr heap);

Binomial_Heap_node_ptr Binomial_Heap_node_create(Application_ptr application);
void Binomial_Heap_node_free(Binomial_Heap_node_ptr node);
status Binomial_Heap_node_copy(Binomial_Heap_node_ptr * to, Binomial_Heap_node_ptr from);

status Binomial_Heap_merge(Binomial_Heap_ptr * res, Binomial_Heap_ptr * first, Binomial_Heap_ptr * second);
status Binomial_Heap_meld(Binomial_Heap_ptr * res, Binomial_Heap_ptr * first, Binomial_Heap_ptr * second);

status Binomial_Heap_get_max(Binomial_Heap_ptr * storage, Application_ptr * res_application);
status Binomial_Heap_delete_max(Binomial_Heap_ptr * storage, Application_ptr * res_application);

status Binomial_Heap_insert(Binomial_Heap_ptr * storage, Application_ptr application);
status Binomial_Heap_set_null(Binomial_Heap_ptr heap);

#endif