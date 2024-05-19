#include "FibonacciHeap.h"
#include <math.h>

Fibonacci_Heap_ptr Fibonacci_Heap_create()
{
    Fibonacci_Heap_ptr heap = (Fibonacci_Heap_ptr)malloc(sizeof(Fibonacci_Heap));
    if (!heap) return NULL;
    heap->size = 0;
    heap->max = NULL;
    return heap;
}

status Fibonacci_Heap_set_null(Fibonacci_Heap_ptr heap)
{
    heap->size = 0;
    heap->max = NULL;
    return success;
}

status Fibonacci_Heap_copy(Fibonacci_Heap_ptr * to, Fibonacci_Heap_ptr from)
{
    if (*to)
    {
        Fibonacci_Heap_free(&from);
        return invalid_function_argument;
    }
    if (!from)
    {
        *to = NULL;
        return success;
    }
    *to = Fibonacci_Heap_create();
    if (!(*to))
    {
        Fibonacci_Heap_free(&from);
        return no_memory;
    }
}

FH_node_ptr Fibonacci_Heap_node_create(Application_ptr application)
{
    FH_node_ptr node = (FH_node_ptr)malloc(sizeof(FH_node));
    if (!node)
    {
        free_application(application);
        return NULL;
    }
    node->application = application;
    node->rank = 0;
    node->child = node->left = node->right = NULL;
    return node;
}

void Fibonacci_Heap_node_free(FH_node_ptr node)
{
    if (!node) return;
    if (node->left) node->left->right = NULL;

    Fibonacci_Heap_node_free(node->child);
    Fibonacci_Heap_node_free(node->right);

    if (node->application) free_application(node->application);

    node->child = node->left = node->right = NULL;
    free(node);
    node = NULL;
}

status Fibonacci_Heap_node_copy(FH_node_ptr * to, FH_node_ptr from)
{
    if (*to) return invalid_function_argument;

    if (!from) return success;

    *to = Fibonacci_Heap_node_create(copy_application(from->application));
    if (!(*to))
    {
        Fibonacci_Heap_node_free(from);
        return no_memory;
    }
    (*to)->rank = from->rank;

    status error;

    if ((error = Fibonacci_Heap_node_copy(&(*to)->child, from->child)) != success || (error = Fibonacci_Heap_node_copy(&(*to)->right, from->right)) != success)
    {
        Fibonacci_Heap_node_free(*to);
        Fibonacci_Heap_node_free(from);
        return error;
    }

    if ((*to)->right)
    {
        (*to)->left = (*to)->right->left;
        (*to)->left->right = (*to);
        (*to)->right->left = (*to);
    }
    else (*to)->left = (*to);

    return success;
}

void Fibonacci_Heap_free(Fibonacci_Heap_ptr * storage)
{
    if (!(*storage)) return;
    if ((*storage)->max) Fibonacci_Heap_node_free((*storage)->max);
    Fibonacci_Heap_set_null(*storage);
    free(*storage);
    *storage = NULL;
}

status Fibonacci_Heap_meld(Fibonacci_Heap_ptr * res, Fibonacci_Heap_ptr * first, Fibonacci_Heap_ptr * second)
{
    if (*res) return invalid_function_argument;
    if (!(*first) && !(*second)) return success;
    if (!(*first))
    {
        *res = *second;
        *second = NULL;
        return success;
    }
    if (!(*second))
    {
        *res = *first;
        *first = NULL;
        return success;
    }
    *res = *first;

    FH_node_ptr tmp = (*res)->max->right;
    (*res)->max->right = (*second)->max;
    (*second)->max->left = (*res)->max;
    tmp->left = (*second)->max;
    (*second)->max->right = tmp;

    if (applications_comparator((*res)->max->application, (*second)->max->application) < 0) (*res)->max = (*second)->max;

    free(*second);
    *second = NULL;
    *first = NULL;

    return success;
}

status Fibonacci_Heap_merge(Fibonacci_Heap_ptr * res, Fibonacci_Heap_ptr * first, Fibonacci_Heap_ptr * second)
{
    Fibonacci_Heap_ptr first_copy = NULL;
    Fibonacci_Heap_ptr second_copy = NULL;
    status error;
    if ((error = Fibonacci_Heap_copy(&first_copy, *first)) != success || (error = Fibonacci_Heap_copy(&second_copy, *second)) != success)
    {
        Fibonacci_Heap_free(first);
        Fibonacci_Heap_free(second);
        return error;
    }

    return Fibonacci_Heap_meld(res, &first_copy, &second_copy);
}

status Fibonacci_Heap_node_merge(Fibonacci_Heap_ptr * storage, FH_node_ptr first, FH_node_ptr second, FH_node_ptr * res)
{
    if (!(*storage) || !first || !second || !res) return invalid_function_argument;

    if (first == second || first->rank != second->rank) return invalid_function_argument;

    if (applications_comparator(first->application, second->application) < 0)
    {
        FH_node_ptr tmp = first;
        first = second;
        second = first;
    }

    if (first->child)
    {
        second->right = first->child;
        second->left = first->child->left;
        second->left->right = second;
        second->right->left = second;
    }
    else
    {
        second->left = second;
        second->right = second;
    }

    first->child = second;
    first->rank++;

    *res = first;

    return success;
}

status Fibonacci_Heap_consolidate(Fibonacci_Heap_ptr * storage)
{
    if (!(*storage)) return invalid_function_argument;

    if (!(*storage)->max || (*storage)->max->right == (*storage)->max) return success;

    FH_node_ptr current = (*storage)->max;
    FH_node_ptr next = current->right;
    size_t size = log2(1.0 * (*storage)->size) + 3;

    FH_node_ptr * array = (FH_node_ptr*)calloc(size, sizeof(FH_node_ptr));
    if (!array)
    {
        Fibonacci_Heap_free(storage);
        return no_memory;
    }

    (*storage)->max->left->right = NULL;

    status error;

    while (current)
    {
        next = current->right;
        if (current->right == current) current->right = NULL;

        while (array[current->rank])
        {
            FH_node_ptr tmp = array[current->rank];
            array[current->rank] = NULL;
            if ((error = Fibonacci_Heap_node_merge(storage, current, tmp, &current)) != success)
            {
                Fibonacci_Heap_free(storage);
                return error;
            }
            array[size - 1] = current;
        }

        array[current->rank] = current;
        current = next;
    }

    FH_node_ptr top = NULL;
    FH_node_ptr start = NULL;
    FH_node_ptr prev = NULL;

    for (size_t i = 0; i < size; ++i)
    {
        if (!array[i]) continue;
        start = start ? start : array[i];
        top = top ? top : array[i];

        if (applications_comparator(array[i]->application, top->application) > 0) top = array[i];
        if (prev) prev->right = array[i];

        array[i]->left = prev;
        prev = array[i];
    }

    prev->right = start;
    start->left = prev;
    (*storage)->max = top;
    free(array);

    return success;
}

status Fibonacci_Heap_get_max(Fibonacci_Heap_ptr * storage, Application_ptr * res_application)
{
    if (!(*storage) || !((*storage)->max))
    {
        Fibonacci_Heap_free(storage);
        return invalid_function_argument;
    }
    *res_application = (*storage)->max->application;
    return success;
}

status Fibonacci_Heap_delete_max(Fibonacci_Heap_ptr * storage, Application_ptr * res_application)
{
    if (!(*storage) || !((*storage)->max))
    {
        Fibonacci_Heap_free(storage);
        return invalid_function_argument;
    }
    *res_application = (*storage)->max->application;

    FH_node_ptr top = (*storage)->max;

    if (top->right == top && !top->child) (*storage)->max = NULL;
    else if (top->right == top) (*storage)->max = (*storage)->max->child;
    else if (!top->child)
    {
        (*storage)->max->left->right = (*storage)->max->right;
        (*storage)->max->right->left = (*storage)->max->left;
        (*storage)->max = (*storage)->max->left;
    }
    else
    {
        (*storage)->max->left->right = (*storage)->max->child;
        (*storage)->max->right->left = (*storage)->max->child->left;
        (*storage)->max->left->right->left = (*storage)->max->left;
        (*storage)->max->right->left->right = (*storage)->max->right;
        (*storage)->max = (*storage)->max->left;
    }

    free(top);
    top = NULL;
    (*storage)->size--;

    return Fibonacci_Heap_consolidate(storage);
}

status Fibonacci_Heap_insert(Fibonacci_Heap_ptr * storage, Application_ptr application)
{
    if (!(*storage) || !application) return invalid_function_argument;

    FH_node_ptr node = Fibonacci_Heap_node_create(application);
    if (!node)
    {
        Fibonacci_Heap_free(storage);
        return no_memory;
    }

    if (!(*storage)->max)
    {
        node->left = node->right = node;
        (*storage)->max = node;
    }
    else
    {
        node->left = (*storage)->max->left;
        node->right = (*storage)->max;
        node->left->right = node;
        node->right->left = node;

        if (applications_comparator(node->application, (*storage)->max->application) > 0) (*storage)->max = node;
    }

    (*storage)->size++;

    return success;
}