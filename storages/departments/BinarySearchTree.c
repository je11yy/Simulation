#include "BinarySearchTree.h"

BST_node_ptr BST_node_create(int key, Department_ptr department)
{
    BST_node_ptr node = (BST_node_ptr)malloc(sizeof(BST_node));
    if (!node) return NULL;
    node->key = key;
    node->department = department;
    node->left = node->right = NULL;
    return node;
}

void BST_node_free(BST_node_ptr node)
{
    if (!node) return;
    BST_node_free(node->left);
    BST_node_free(node->right);
    department_free(node->department);
    free(node);
}

BST_ptr BST_create()
{
    BST_ptr bst = (BST_ptr)malloc(sizeof(BST));
    if (!bst) return NULL;
    bst->root = NULL;
    return bst;
}

status BST_set_null(BST_ptr bst)
{
    bst->root = NULL;
    return success;
}

void BST_free(BST_ptr bst)
{
    BST_node_free(bst->root);
    free(bst);
}

status BST_insert(BST_ptr tree, int key, Department_ptr department)
{
    if (!tree || !department) return invalid_function_argument;
    
    if (!tree->root)
    {
        tree->root = BST_node_create(key, department);
        if (!tree->root) return no_memory;
        return success;
    }

    BST_node_ptr current = tree->root;
    BST_node_ptr parent = NULL;

    while (current)
    {
        parent = current;
        if (key == current->key) return already_existing_key;
        if (key < current->key) current = current->left;
        else current = current->right;
    }

    if (key < parent->key)
    {
        parent->left = BST_node_create(key, department);
        if (!parent->left) return no_memory;
        return success;
    }
    parent->right = BST_node_create(key, department);
    if (!parent->right) return no_memory;
    return success;
}

void BST_find_node(BST_ptr tree, int key, BST_node_ptr * node)
{
    if (!tree->root) return;

    BST_node_ptr current = tree->root;

    while (current)
    {
        if (key == current->key)
        {
            *node = current;
            return;
        }
        else if(key < current->key) current = current->left;
        else current = current->right;
    }
}

status BST_find(BST_ptr tree, int key, Department_ptr * department)
{
    if (!tree || *department) return invalid_function_argument;

    BST_node_ptr node = NULL;
    BST_find_node(tree, key, &node);
    if (!node) return cannot_find;
    *department = node->department;
    return success;
}