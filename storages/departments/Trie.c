#include "Trie.h"

Trie_node_ptr Trie_node_create()
{
    Trie_node_ptr node = (Trie_node_ptr)malloc(sizeof(Trie_node));
    node->department = NULL;
    if (!node) return NULL;
    for (int i = 0; i < DIGITS_NUMBER; ++i) node->childs[i] = NULL;
    return node;
}

void Trie_node_free(Trie_node_ptr node)
{
    if (!node) return;
    for (int i = 0; i < DIGITS_NUMBER; ++i) Trie_node_free(node->childs[i]);
    department_free(node->department);
    free(node);
    node = NULL;
}

status Trie_set_null(Trie_ptr tree)
{
    tree->root = NULL;
    return success;
}

Trie_ptr Trie_create()
{
    Trie_ptr tree = (Trie_ptr)malloc(sizeof(Trie));
    if (!tree) return NULL;
    tree->root = Trie_node_create();
    if (!tree->root)
    {
        free(tree);
        return NULL;
    }
    return tree;
}

void Trie_free(Trie_ptr tree)
{
    Trie_node_free(tree->root);
    free(tree);
    tree = NULL;
}

int find_digits_count_in_number(int number)
{
    if (!number/10) return 1;
    int result = 0;
    while (number > 0)
    {
        number/=10;
        result++;

    }
    return result;
}

status Trie_find(Trie_ptr tree, int key, Department_ptr * result)
{
    if (!tree) return invalid_function_argument;

    int string_size = find_digits_count_in_number(key);
    char key_string[string_size];
    sprintf(key_string, "%d", key);

    Trie_node_ptr current = tree->root;
    
    for (int i = 0; i < string_size; ++i)
    {
        int digit = key_string[i] - '0';
        if (!current->childs[digit]) return cannot_find;
        current = current->childs[digit];
    }
    if (!current->department) return cannot_find;
    *result = current->department;
    return success;
}

status Trie_insert(Trie_ptr tree, int key, Department_ptr department)
{
    if (!tree || !department) return invalid_function_argument;

    int string_size = find_digits_count_in_number(key);
    char key_string[string_size];
    sprintf(key_string, "%d", key);

    Trie_node_ptr current = tree->root;

    for (int i = 0; i < string_size; ++i)
    {
        int digit = key_string[i] - '0';
        if (!current->childs[digit])
        {
            Trie_node_ptr new_node = Trie_node_create();
            if (!new_node) return no_memory;
            current->childs[digit] = new_node;
        }
        current = current->childs[digit];
    }
    current->department = department;
    return success;
}