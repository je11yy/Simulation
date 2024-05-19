#include "department_storage.h"


Department_storage_ptr department_storage_create(department_type type)
{
    Department_storage_ptr department_storage = (Department_storage_ptr)malloc(sizeof(Department_storage));
    if (!department_storage) return NULL;
    department_storage->type = type;
    void * storage = NULL;
    switch (type)
    {
        case HashSet_T:
            storage = HS_create();
            if (!storage)
            {
                free(department_storage);
                return NULL;
            }
            department_storage->insert   =     (status (*) (void *, int, Department_ptr)) HS_insert;
            department_storage->find     =   (status (*) (void *, int, Department_ptr *)) HS_find;
            department_storage->free     =                            (void (*) (void *)) HS_free;
            department_storage->set_null =                       (status (*) (void*)) HS_set_null;
            break;
        case DynamicArray_T:
            storage = dynamic_array_create();
            if (!storage)
            {
                free(department_storage);
                return NULL;
            }
            department_storage->insert   =     (status (*) (void *, int, Department_ptr)) dynamic_array_insert;
            department_storage->find     =   (status (*) (void *, int, Department_ptr *)) dynamic_array_find;
            department_storage->free     =                            (void (*) (void *)) dynamic_array_free;
            department_storage->set_null =                           (status (*) (void*)) dynamic_array_set_null;
            break;
        case BST_T:
            storage = BST_create();
            if (!storage)
            {
                free(department_storage);
                return NULL;
            }
            department_storage->insert   =     (status (*) (void *, int, Department_ptr)) BST_insert;
            department_storage->find     =   (status (*) (void *, int, Department_ptr *)) BST_find;
            department_storage->free     =                            (void (*) (void *)) BST_free;
            department_storage->set_null =                           (status (*) (void*)) BST_set_null;
            break; 
        case Trie_T:
            storage = Trie_create();
            if (!storage)
            {
                free(department_storage);
                return NULL;
            }
            department_storage->insert   =     (status (*) (void *, int, Department_ptr)) Trie_insert;
            department_storage->find     =   (status (*) (void *, int, Department_ptr *)) Trie_find;
            department_storage->free     =                            (void (*) (void *)) Trie_free;
            department_storage->set_null =                           (status (*) (void*)) Trie_set_null;
            break;
    }
    department_storage->storage = storage;
    return department_storage;
}

status departments_storage_insert_application(Department_storage_ptr departments, Application_ptr application)
{
    status error;
    Department_ptr dep = NULL;
    if ((error = departments->find(departments->storage, application->department_id, &dep)) != success) return error;
    if ((error = department_insert_application(dep, application)) != success) return error;
    return success;
}