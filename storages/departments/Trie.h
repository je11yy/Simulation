#ifndef _TRIE_H_
#define _TRIE_H_

#include "department.h"

#define DIGITS_NUMBER 10

typedef struct Trie_node
{
    // от 0 до 9
    struct Trie_node * childs[DIGITS_NUMBER];
    Department_ptr department;
    
} Trie_node, *Trie_node_ptr;

typedef struct Trie
{
    Trie_node_ptr root;
} Trie, *Trie_ptr;

Trie_node_ptr Trie_node_create();
void Trie_node_free(Trie_node_ptr node);

Trie_ptr Trie_create();
void Trie_free(Trie_ptr tree);

int find_digits_count_in_number(int number);

status Trie_find(Trie_ptr tree, int key, Department_ptr * result);
status Trie_insert(Trie_ptr tree, int key, Department_ptr department);
status Trie_set_null(Trie_ptr tree);

#endif