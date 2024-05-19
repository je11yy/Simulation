#ifndef _SKEW_HEAP_H
#define _SKEW_HEAP_H

#include "../../application.h"

typedef struct Skew_node
{
    Application_ptr application;
    struct Skew_node * left;
    struct Skew_node * right;

} Skew_node, *Skew_node_ptr;


typedef struct Skew_Heap
{
   Skew_node_ptr head;
   size_t size;

} Skew_Heap, *Skew_Heap_ptr;

Skew_Heap_ptr Skew_Heap_create();
void Skew_Heap_free(Skew_Heap_ptr * storage);
status Skew_Heap_copy(Skew_Heap_ptr * to, Skew_Heap_ptr from);

Skew_node_ptr Skew_Heap_node_create(Application_ptr application);
void Skew_Heap_node_free(Skew_node_ptr node);
status Skew_Heap_node_copy(Skew_node_ptr * to, Skew_node_ptr from);

status Skew_Heap_set_null(Skew_Heap_ptr heap);

status Skew_Heap_meld(Skew_Heap_ptr * res, Skew_Heap_ptr * first, Skew_Heap_ptr * second);
status Skew_Heap_merge(Skew_Heap_ptr * res, Skew_Heap_ptr * first, Skew_Heap_ptr * second);

status Skew_Heap_get_max(Skew_Heap_ptr * storage, Application_ptr * res_application);
status Skew_Heap_delete_max(Skew_Heap_ptr * storage, Application_ptr * res_application);

status Skew_Heap_insert(Skew_Heap_ptr * storage, Application_ptr application);

Skew_node_ptr Skew_Heap_node_merge(Skew_node_ptr first, Skew_node_ptr second);


#endif