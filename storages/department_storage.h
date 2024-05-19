#ifndef _DEPARTMENT_STORAGE_H_
#define _DEPARTMENT_STORAGE_H_

#include "departments/HashSet.h"
#include "departments/DynamicArray.h"
#include "departments/BinarySearchTree.h"
#include "departments/Trie.h"

typedef enum department_type
{
    HashSet_T = 0,
    DynamicArray_T = 1,
    BST_T = 2,
    Trie_T = 3
} department_type;

typedef struct Department_storage
{
    void * storage;
    department_type type;

    size_t size;

    status (*insert) (void * storage, int key, Department_ptr dep);
    status (*find) (void * storage, int key, Department_ptr * dep);
    status (*set_null) (void * storage);

    void (*free) (void * storage);

} Department_storage, *Department_storage_ptr;

Department_storage_ptr department_storage_create(department_type type);


status departments_storage_insert_application(Department_storage_ptr departments, Application_ptr application);

#endif