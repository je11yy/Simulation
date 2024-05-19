#ifndef _LEFTIST_HEAP_H
#define _LEFTIST_HEAP_H

#include "../../application.h"

typedef struct Leftist_node
{
    Application_ptr application;
    int distance;
    struct Leftist_node * left;
    struct Leftist_node * right;

} Leftist_node, *Leftist_node_ptr;

typedef struct Leftist_Heap
{
    Leftist_node_ptr head;
    size_t size;
    
} Leftist_Heap, *Leftist_Heap_ptr;

Leftist_Heap_ptr Leftist_Heap_create();
void Leftist_Heap_free(Leftist_Heap_ptr * storage);
status Leftist_Heap_copy(Leftist_Heap_ptr * to, Leftist_Heap_ptr from);

Leftist_node_ptr Leftist_Heap_node_create(Application_ptr application);
void Leftist_Heap_node_free(Leftist_node_ptr node);
status Leftist_Heap_node_copy(Leftist_node_ptr * to, Leftist_node_ptr from);

status Leftist_Heap_set_null(Leftist_Heap_ptr heap);

status Leftist_Heap_meld(Leftist_Heap_ptr * res, Leftist_Heap_ptr * first, Leftist_Heap_ptr * second);
status Leftist_Heap_merge(Leftist_Heap_ptr * res, Leftist_Heap_ptr * first, Leftist_Heap_ptr * second);

status Leftist_Heap_get_max(Leftist_Heap_ptr * storage, Application_ptr * res_application);
status Leftist_Heap_delete_max(Leftist_Heap_ptr * storage, Application_ptr * res_application);

status Leftist_Heap_insert(Leftist_Heap_ptr * storage, Application_ptr application);

Leftist_node_ptr Leftist_Heap_node_merge(Leftist_node_ptr first, Leftist_node_ptr second);


#endif