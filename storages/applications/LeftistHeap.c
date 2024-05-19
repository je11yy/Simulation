#include "LeftistHeap.h"

Leftist_Heap_ptr Leftist_Heap_create()
{
    Leftist_Heap_ptr heap = (Leftist_Heap_ptr)malloc(sizeof(Leftist_Heap));
    if (!heap) return NULL;
    heap->head = NULL;
    heap->size = 0;
    return heap;
}

status Leftist_Heap_set_null(Leftist_Heap_ptr heap)
{
    heap->head = NULL;
    heap->size = 0;
    return success;
}

void Leftist_Heap_free(Leftist_Heap_ptr * storage)
{
    if (!(*storage)) return;
    if ((*storage)->head) Leftist_Heap_node_free((*storage)->head);
    free(*storage);
    *storage = NULL;
}

status Leftist_Heap_copy(Leftist_Heap_ptr * to, Leftist_Heap_ptr from)
{
    if (*to || !from) return invalid_function_argument;
    status error;
    if ((error = Leftist_Heap_node_copy(&(*to)->head, from->head)) != success)
    {
        Leftist_Heap_free(to);
        Leftist_Heap_free(&from);
        return error;
    }

    (*to)->size = from->size;

    return success;
}

Leftist_node_ptr Leftist_Heap_node_create(Application_ptr application)
{
    Leftist_node_ptr node = (Leftist_node_ptr)malloc(sizeof(Leftist_node));
    if (!node)
    {
        free_application(application);
        return NULL;
    }
    node->application = application;
    node->distance = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void Leftist_Heap_node_free(Leftist_node_ptr node)
{
    if (!node) return;
    Leftist_Heap_node_free(node->left);
    Leftist_Heap_node_free(node->right);

    if (node->application) free_application(node->application);
    free(node);
    node = NULL;
}

status Leftist_Heap_node_copy(Leftist_node_ptr * to, Leftist_node_ptr from)
{
    if (*to)
    {
        Leftist_Heap_node_free(from);
        return invalid_function_argument;
    }

    if (!from)
    {
        *to = NULL;
        return success;
    }

    Leftist_node_ptr new = Leftist_Heap_node_create(copy_application(from->application));
    if (!new)
    {
        Leftist_Heap_node_free(from);
        return no_memory;
    }

    new->distance = from->distance;

    status error;
    if ((error = Leftist_Heap_node_copy(&new->right, from->right)) != success || (error = Leftist_Heap_node_copy(&new->left, from->left)) != success)
    {
        Leftist_Heap_node_free(from);
        Leftist_Heap_node_free(*to);
        return error;
    }

    *to = new;

    return success;
}

status Leftist_Heap_meld(Leftist_Heap_ptr * res, Leftist_Heap_ptr * first, Leftist_Heap_ptr * second)
{
    if (!(*first) || !(*second) || *first == *second) return invalid_function_argument;

    Leftist_Heap_ptr tmp = Leftist_Heap_create();
    if (!tmp)
    {
        Leftist_Heap_free(first);
        Leftist_Heap_free(second);
        return no_memory;
    }
    tmp->head = Leftist_Heap_node_merge((*second)->head, (*first)->head);
    tmp->size = (*first)->size + (*second)->size;

    (*first)->head = (*second)->head = NULL;
    (*first)->size = (*second)->size = 0;
    Leftist_Heap_free(first);
    Leftist_Heap_free(second);

    *res = tmp;

    return success;
}

status Leftist_Heap_merge(Leftist_Heap_ptr * res, Leftist_Heap_ptr * first, Leftist_Heap_ptr * second)
{
    Leftist_Heap_ptr first_copy = NULL;
    Leftist_Heap_ptr second_copy = NULL;
    status error;
    if ((error = Leftist_Heap_copy(&first_copy, *first)) != success || (error = Leftist_Heap_copy(&second_copy, *second)) != success)
    {
        Leftist_Heap_free(first);
        Leftist_Heap_free(second);
        return error;
    }

    return Leftist_Heap_meld(res, &first_copy, &second_copy);
}

status Leftist_Heap_get_max(Leftist_Heap_ptr * storage, Application_ptr * res_application)
{
    if (!(*storage) || *res_application) return invalid_function_argument;

    if (!(*storage)->head) return success;

    *res_application = (*storage)->head->application;
    return success;
}

Leftist_node_ptr Leftist_Heap_node_merge(Leftist_node_ptr first, Leftist_node_ptr second)
{
    if (!first && !second) return NULL;
    if (!first) return second;
    if (!second) return first;

    if (applications_comparator(first->application, second->application) < 0)
    {
        Leftist_node_ptr tmp = first;
        first = second;
        second = tmp;
    }

    first->right = Leftist_Heap_node_merge(first->right, second);

    if (first->right && (!first->left || first->left->distance < first->right->distance))
    {
        Leftist_node_ptr tmp = first->left;
        first->left = first->right;
        first->right = tmp;
    }

    first->distance = first->right == NULL ? 0 : first->right->distance + 1;

    return first;
}

status Leftist_Heap_delete_max(Leftist_Heap_ptr * storage, Application_ptr * res_application)
{
    if (!(*storage) || *res_application) return invalid_function_argument;

    if (!(*storage)->head) return success;

    *res_application = (*storage)->head->application;   
    Leftist_node_ptr head = (*storage)->head;

    (*storage)->head = Leftist_Heap_node_merge((*storage)->head->right, (*storage)->head->left);

    free(head);
    head = NULL;
    (*storage)->size--;

    return success;
}

status Leftist_Heap_insert(Leftist_Heap_ptr * storage, Application_ptr application)
{
    if (!(*storage) || !application) return invalid_function_argument;

    Leftist_node_ptr node = Leftist_Heap_node_create(application);
    if (!node)
    {
        Leftist_Heap_free(storage);
        free_application(application);
        return no_memory;
    }

    Leftist_Heap_ptr tmp = Leftist_Heap_create();
    if (!tmp)
    {
        Leftist_Heap_free(storage);
        free_application(application);
        Leftist_Heap_node_free(node);
        return no_memory;
    }
    tmp->head = node;
    tmp->size = 1;

    Leftist_Heap_ptr new = NULL;
    status error;
    if ((error = Leftist_Heap_meld(&new, storage, &tmp)) != success)
    {
        Leftist_Heap_free(storage);
        Leftist_Heap_free(&tmp);
        free_application(application);
        Leftist_Heap_node_free(node);
        return no_memory;
    }
    *storage = new;
    return success;
}