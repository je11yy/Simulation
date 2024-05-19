#include "SkewHeap.h"

Skew_Heap_ptr Skew_Heap_create()
{
    Skew_Heap_ptr heap = (Skew_Heap_ptr)malloc(sizeof(Skew_Heap));
    if (!heap) return NULL;
    heap->head = NULL;
    heap->size = 0;
    return heap;
}

status Skew_Heap_set_null(Skew_Heap_ptr heap)
{
    heap->head = NULL;
    heap->size = 0;
    return success;
}

void Skew_Heap_free(Skew_Heap_ptr * storage)
{
    if (!(*storage)) return;
    if ((*storage)->head) Skew_Heap_node_free((*storage)->head);
    free(*storage);
    *storage = NULL;
}

status Skew_Heap_copy(Skew_Heap_ptr * to, Skew_Heap_ptr from)
{
    if (*to || !from) return invalid_function_argument;
    status error;
    if ((error = Skew_Heap_node_copy(&(*to)->head, from->head)) != success)
    {
        Skew_Heap_free(to);
        Skew_Heap_free(&from);
        return error;
    }

    (*to)->size = from->size;

    return success;
}

Skew_node_ptr Skew_Heap_node_create(Application_ptr application)
{
    Skew_node_ptr node = (Skew_node_ptr)malloc(sizeof(Skew_node));
    if (!node)
    {
        free_application(application);
        return NULL;
    }
    node->application = application;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void Skew_Heap_node_free(Skew_node_ptr node)
{
    if (!node) return;
    Skew_Heap_node_free(node->right);
    Skew_Heap_node_free(node->left);

    if (node->application) free_application(node->application);
    free(node);
    node = NULL;
}

status Skew_Heap_node_copy(Skew_node_ptr * to, Skew_node_ptr from)
{
    if (*to)
    {
        Skew_Heap_node_free(from);
        return invalid_function_argument;
    }

    if (!from)
    {
        *to = NULL;
        return success;
    }

    Skew_node_ptr new = Skew_Heap_node_create(copy_application(from->application));
    if (!new)
    {
        Skew_Heap_node_free(from);
        return no_memory;
    }

    status error;
    if ((error = Skew_Heap_node_copy(&new->right, from->right)) != success || (error = Skew_Heap_node_copy(&new->left, from->left)) != success)
    {
        Skew_Heap_node_free(from);
        Skew_Heap_node_free(*to);
        return error;
    }

    *to = new;

    return success;
}

status Skew_Heap_meld(Skew_Heap_ptr * res, Skew_Heap_ptr * first, Skew_Heap_ptr * second)
{
    if (!(*first) || !(*second) || *first == *second) return invalid_function_argument;

    Skew_Heap_ptr tmp = Skew_Heap_create();
    if (!tmp)
    {
        Skew_Heap_free(first);
        Skew_Heap_free(second);
        return no_memory;
    }
    tmp->head = Skew_Heap_node_merge((*second)->head, (*first)->head);
    tmp->size = (*first)->size + (*second)->size;

    (*first)->head = (*second)->head = NULL;
    (*first)->size = (*second)->size = 0;
    Skew_Heap_free(first);
    Skew_Heap_free(second);

    *res = tmp;

    return success;
}

status Skew_Heap_merge(Skew_Heap_ptr * res, Skew_Heap_ptr * first, Skew_Heap_ptr * second)
{
    Skew_Heap_ptr first_copy = NULL;
    Skew_Heap_ptr second_copy = NULL;
    status error;
    if ((error = Skew_Heap_copy(&first_copy, *first)) != success || (error = Skew_Heap_copy(&second_copy, *second)) != success)
    {
        Skew_Heap_free(first);
        Skew_Heap_free(second);
        return error;
    }

    return Skew_Heap_meld(res, &first_copy, &second_copy);
}

status Skew_Heap_get_max(Skew_Heap_ptr * storage, Application_ptr * res_application)
{
    if (!(*storage) || *res_application) return invalid_function_argument;

    if (!(*storage)->head) return success;

    *res_application = (*storage)->head->application;
    return success;
}

status Skew_Heap_delete_max(Skew_Heap_ptr * storage, Application_ptr * res_application)
{
    if (!(*storage) || *res_application) return invalid_function_argument;

    if (!(*storage)->head) return success;

    *res_application = (*storage)->head->application;   
    Skew_node_ptr head = (*storage)->head;

    (*storage)->head = Skew_Heap_node_merge((*storage)->head->right, (*storage)->head->left);

    free(head);
    head = NULL;
    (*storage)->size--;

    return success;
}

status Skew_Heap_insert(Skew_Heap_ptr * storage, Application_ptr application)
{
    if (!(*storage) || !application) return invalid_function_argument;

    Skew_node_ptr node = Skew_Heap_node_create(application);
    if (!node)
    {
        Skew_Heap_free(storage);
        free_application(application);
        return no_memory;
    }

    Skew_Heap_ptr tmp = Skew_Heap_create();
    if (!tmp)
    {
        Skew_Heap_free(storage);
        free_application(application);
        Skew_Heap_node_free(node);
        return no_memory;
    }
    tmp->head = node;
    tmp->size = 1;

    Skew_Heap_ptr new = NULL;
    status error;
    if ((error = Skew_Heap_meld(&new, storage, &tmp)) != success)
    {
        Skew_Heap_free(storage);
        Skew_Heap_free(&tmp);
        free_application(application);
        Skew_Heap_node_free(node);
        return no_memory;
    }
    *storage = new;
    return success;
}

Skew_node_ptr Skew_Heap_node_merge(Skew_node_ptr first, Skew_node_ptr second)
{
    if (!first && !second) return NULL;
    if (!first) return second;
    if (!second) return first;

    if (applications_comparator(first->application, second->application) < 0)
    {
        Skew_node_ptr tmp = first;
        first = second;
        second = tmp;
    }

    first->left = Skew_Heap_node_merge(second, first->left);

    Skew_node_ptr tmp = first->left;
    first->left = first->right;
    first->right = tmp;

    return first;
}