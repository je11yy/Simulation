#ifndef _TREAP_H
#define _TREAP_H

#include "../../application.h"

typedef struct Treap_node
{
    Application_ptr application;
    int priority;
    struct Treap_node * left;
    struct Treap_node * right;
} Treap_node, *Treap_node_ptr;

typedef struct Treap
{
    Treap_node_ptr root;
    size_t size;
} Treap, *Treap_ptr;

Treap_ptr Treap_create();
void Treap_free(Treap_ptr * storage);
status Treap_copy(Treap_ptr * to, Treap_ptr from);

Treap_node_ptr Treap_node_create(Application_ptr application);
void Treap_node_free(Treap_node_ptr node);
status Treap_node_copy(Treap_node_ptr * to, Treap_node_ptr from);

status Treap_insert(Treap_ptr * storage, Application_ptr application);

status Treap_split(Treap_node_ptr node, Application_ptr application, Treap_node_ptr * first, Treap_node_ptr * second);
Treap_node_ptr Treap_node_merge(Treap_node_ptr first, Treap_node_ptr second);

status Treap_meld(Treap_ptr * res, Treap_ptr * first, Treap_ptr * second);
status Treap_merge(Treap_ptr * res, Treap_ptr * first, Treap_ptr * second);

status Treap_get_max(Treap_ptr * storage, Application_ptr * res_application);
status Treap_delete_max(Treap_ptr * storage, Application_ptr * res_application);
status Treap_set_null(Treap_ptr heap);
#endif