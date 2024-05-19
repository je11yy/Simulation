#include "application_storage.h"

Application_storage_ptr application_storage_create(application_storage_type type)
{
    Application_storage_ptr storage = (Application_storage_ptr)malloc(sizeof(Application_storage));
    if (!storage) return NULL;

    void * ds = NULL;
    storage->type = type;

    switch (type)
    {
    case BinaryHeap_T:
        ds = Binary_Heap_create();
        if (!ds)
        {
            free(storage);
            return NULL;
        }
        storage->free = (void (*)(void **)) Binary_Heap_free;
        storage->insert = (status (*)(void **, Application_ptr application)) Binary_Heap_insert;
        storage->get_max = (status (*)(void **, Application_ptr * res_application)) Binary_Heap_get_max;
        storage->delete_max = (status (*)(void **, Application_ptr * res_application)) Binary_Heap_delete_max;
        storage->merge = (status (*)(void **, void **, void **)) Binary_Heap_merge;
        storage->meld = (status (*)(void **, void **, void **)) Binary_Heap_meld;
        storage->set_null = (status (*) (void *)) Binary_Heap_set_null;
        break;
    
    case BinomialHeap_T:
        ds = Binomial_Heap_create();
        if (!ds)
        {
            free(storage);
            return NULL;
        }
        storage->free = (void (*)(void **)) Binomial_Heap_free;
        storage->insert = (status (*)(void **, Application_ptr application)) Binomial_Heap_insert;
        storage->get_max = (status (*)(void **, Application_ptr * res_application)) Binomial_Heap_get_max;
        storage->delete_max = (status (*)(void **, Application_ptr * res_application)) Binomial_Heap_delete_max;
        storage->merge = (status (*)(void **, void **, void **)) Binomial_Heap_merge;
        storage->meld = (status (*)(void **, void **, void **)) Binomial_Heap_meld;
        storage->set_null = (status (*) (void *)) Binomial_Heap_set_null;
        break;
    
    case FibonacciHeap_T:
        ds = Fibonacci_Heap_create();
        if (!ds)
        {
            free(storage);
            return NULL;
        }
        storage->free = (void (*)(void **)) Fibonacci_Heap_free;
        storage->insert = (status (*)(void **, Application_ptr application)) Fibonacci_Heap_insert;
        storage->get_max = (status (*)(void **, Application_ptr * res_application)) Fibonacci_Heap_get_max;
        storage->delete_max = (status (*)(void **, Application_ptr * res_application)) Fibonacci_Heap_delete_max;
        storage->merge = (status (*)(void **, void **, void **)) Fibonacci_Heap_merge;
        storage->meld = (status (*)(void **, void **, void **)) Fibonacci_Heap_meld;
        storage->set_null = (status (*) (void *)) Fibonacci_Heap_set_null;
        break;
    
    case SkewHeap_T:
        ds = Skew_Heap_create();
        if (!ds)
        {
            free(storage);
            return NULL;
        }
        storage->free = (void (*)(void **)) Skew_Heap_free;
        storage->insert = (status (*)(void **, Application_ptr application)) Skew_Heap_insert;
        storage->get_max = (status (*)(void **, Application_ptr * res_application)) Skew_Heap_get_max;
        storage->delete_max = (status (*)(void **, Application_ptr * res_application)) Skew_Heap_delete_max;
        storage->merge = (status (*)(void **, void **, void **)) Skew_Heap_merge;
        storage->meld = (status (*)(void **, void **, void **)) Skew_Heap_meld;
        storage->set_null = (status (*) (void *)) Skew_Heap_set_null;
        break;
    
    case LeftistHeap_T:
        ds = Leftist_Heap_create();
        if (!ds)
        {
            free(storage);
            return NULL;
        }
        storage->free = (void (*)(void **)) Leftist_Heap_free;
        storage->insert = (status (*)(void **, Application_ptr application)) Leftist_Heap_insert;
        storage->get_max = (status (*)(void **, Application_ptr * res_application)) Leftist_Heap_get_max;
        storage->delete_max = (status (*)(void **, Application_ptr * res_application)) Leftist_Heap_delete_max;
        storage->merge = (status (*)(void **, void **, void **)) Leftist_Heap_merge;
        storage->meld = (status (*)(void **, void **, void **)) Leftist_Heap_meld;
        storage->set_null = (status (*) (void *)) Leftist_Heap_set_null;
        break;
    
    case Treap_T:
        ds = Treap_create();
        if (!ds)
        {
            free(storage);
            return NULL;
        }
        storage->free = (void (*)(void **)) Treap_free;
        storage->insert = (status (*)(void **, Application_ptr application)) Treap_insert;
        storage->get_max = (status (*)(void **, Application_ptr * res_application)) Treap_get_max;
        storage->delete_max = (status (*)(void **, Application_ptr * res_application)) Treap_delete_max;
        storage->merge = (status (*)(void **, void **, void **)) Treap_merge;
        storage->meld = (status (*)(void **, void **, void **)) Treap_meld;
        storage->set_null = (status (*) (void *)) Treap_set_null;
        break;
    
    default:
        return NULL;
        break;
    }
    storage->storage = ds;
    return storage;
}

void application_storage_free(Application_storage_ptr storage)
{
    storage->free(&storage->storage);
    free(storage);
    storage = NULL;
}