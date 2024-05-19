#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include "department.h"

typedef struct BST_node
{
    int key;
    Department_ptr department;
    struct BST_node * left;
    struct BST_node * right;

} BST_node, *BST_node_ptr;

typedef struct BST
{
    BST_node_ptr root;

} BST, *BST_ptr;

BST_node_ptr BST_node_create(int key, Department_ptr department);
void BST_node_free(BST_node_ptr node);

BST_ptr BST_create();
void BST_free(BST_ptr bst);

status BST_insert(BST_ptr tree, int key, Department_ptr department);
void BST_find_node(BST_ptr tree, int key, BST_node_ptr * node);
status BST_find(BST_ptr tree, int key, Department_ptr * department);
status BST_set_null(BST_ptr bst);

#endif