#include "BinomialHeap.h"

Binomial_Heap_ptr Binomial_Heap_create()
{
    Binomial_Heap_ptr heap = (Binomial_Heap_ptr)malloc(sizeof(Binomial_Heap));
    if (!heap) return NULL;
    heap->head = NULL;
    heap->max = NULL;
    return heap;
}

status Binomial_Heap_set_null(Binomial_Heap_ptr heap)
{
    heap->head = NULL;
    heap->max = NULL;
    return success;
}

void Binomial_Heap_free(Binomial_Heap_ptr * storage)
{
    if (!(*storage)) return;
    if ((*storage)->head) Binomial_Heap_node_free((*storage)->head);
    free(*storage);
    *storage = NULL;
}

Binomial_Heap_node_ptr Binomial_Heap_node_create(Application_ptr application) 
{
    Binomial_Heap_node_ptr node = (Binomial_Heap_node_ptr)malloc(sizeof(Binomial_Heap_node));
    if (!node)
    {
        free_application(application);
        return NULL;
    }
    node->application = application;
    node->degree = 0;
    node->son = NULL;
    node->brother = NULL;
    return node;
}

void Binomial_Heap_node_free(Binomial_Heap_node_ptr node)
{
    if (!node) return;
    Binomial_Heap_node_free(node->son);
    Binomial_Heap_node_free(node->brother);
    free_application(node->application);
    free(node);
}

status Binomial_Heap_node_copy(Binomial_Heap_node_ptr * to, Binomial_Heap_node_ptr from)
{
    *to = NULL;
    if (from == NULL) return success;
    Binomial_Heap_node_ptr tmp = Binomial_Heap_node_create(copy_application(from->application));
    if (!tmp) return no_memory;

    tmp->degree = from->degree;
    if (Binomial_Heap_node_copy(&tmp->son, from->son) != success || Binomial_Heap_node_copy(&tmp->brother, from->brother) != success)
    {
        Binomial_Heap_node_free(tmp);
        return no_memory;
    }
    *to = tmp;
    return success;
}

Binomial_Heap_ptr Binomial_Heap_copy(Binomial_Heap_ptr heap)
{
    if (!heap) return NULL;

    Binomial_Heap_ptr new = Binomial_Heap_create();
    if (!new) return NULL;
    if (Binomial_Heap_node_copy(&new->head, heap->head) != success) return NULL;
    return new;
}

status Binomial_Heap_merge(Binomial_Heap_ptr * res, Binomial_Heap_ptr * first, Binomial_Heap_ptr * second)
{
    if ((*res) || !(*first) || !(*second))
    {
        Binomial_Heap_free(first);
        Binomial_Heap_free(second);
        return invalid_function_argument;
    }

    Binomial_Heap_ptr copy_first = Binomial_Heap_copy(*first);
    if (!copy_first)
    {
        Binomial_Heap_free(first);
        Binomial_Heap_free(second);
        return no_memory;
    }

    Binomial_Heap_ptr copy_second = Binomial_Heap_copy(*second);
    if (!copy_second)
    {
        Binomial_Heap_free(first);
        Binomial_Heap_free(second);
        Binomial_Heap_free(&copy_first);
        return no_memory;
    }

    if (Binomial_Heap_meld(res, &copy_first, &copy_second) == no_memory)
    {
        Binomial_Heap_free(first);
        Binomial_Heap_free(second);
        return no_memory;
    }
    return success;
}

status Binomial_Heap_meld(Binomial_Heap_ptr * res, Binomial_Heap_ptr * first, Binomial_Heap_ptr * second)
{
    if ((*res) || !(*first) || !(*second))
    {
        Binomial_Heap_free(first);
        Binomial_Heap_free(second);
        return invalid_function_argument;
    }
    
    Binomial_Heap_node_ptr left_iterator = (*first)->head;
    Binomial_Heap_node_ptr right_iterator = (*second)->head;

    if (!left_iterator && !right_iterator)
    {
        *res = Binomial_Heap_create();
        if (!(*res))
        {
            Binomial_Heap_free(first);
            Binomial_Heap_free(second);
            return no_memory;
        }
        Binomial_Heap_free(first);
        Binomial_Heap_free(second);
        return success;
    }

    Binomial_Heap_ptr tmp = Binomial_Heap_create();
    if (!tmp)
    {
        Binomial_Heap_free(first);
        Binomial_Heap_free(second);
        return invalid_function_argument;
    }

    if (left_iterator && (!right_iterator || left_iterator->degree < right_iterator->degree))
    {
        tmp->head = left_iterator;
        left_iterator = left_iterator->brother;
    }
    else
    {
        tmp->head = right_iterator;
        right_iterator = right_iterator->brother;
    }

    Binomial_Heap_node_ptr result_iterator = tmp->head;
    while (left_iterator && right_iterator)
    {
        if (left_iterator->degree < right_iterator->degree)
        {
            result_iterator->brother = left_iterator;
            left_iterator = left_iterator->brother;
        }
        else
        {
            result_iterator->brother = right_iterator;
            right_iterator = right_iterator->brother;
        }
        result_iterator = result_iterator->brother;
    }

    while (left_iterator)
    {
        result_iterator->brother = left_iterator;
        left_iterator = left_iterator->brother;
        result_iterator = result_iterator->brother;
    }

    while (right_iterator)
    {
        result_iterator->brother = right_iterator;
        right_iterator = right_iterator->brother;
        result_iterator = result_iterator->brother;
    }


    Binomial_Heap_node_ptr prev = NULL;
    Binomial_Heap_node_ptr current = tmp->head;
    Binomial_Heap_node_ptr right = tmp->head->brother;

    while (right)
    {
        Binomial_Heap_node_ptr tmp_node = right->brother;
        if (current->degree == right->degree && (!tmp_node || tmp_node->degree != right->degree))
        {
            if (applications_comparator(current->application, right->application) > 0)
            {
                right->brother = current->son;
                current->son = right;
            }
            else
            {
                current->brother = right->son;
                right->son = current;

                if (current == tmp->head) tmp->head = right;
                current = right;
            }
            if (prev) prev->brother = current;
            current->degree++;
            current->brother = tmp_node;
            right = tmp_node;
        }
        else
        {
            prev = current;
            current = right;
            right = right->brother;
        }
    }
    (*first)->head = (*second)->head = NULL;
    (*first)->max = (*second)->max = NULL;
    free(*first);
    free(*second);

    *res = tmp;
    return success;
}

status Binomial_Heap_get_max(Binomial_Heap_ptr * storage, Application_ptr * res_application)
{
    if (!(*storage) || (*res_application))
    {
        Binomial_Heap_free(storage);
        return invalid_function_argument;
    }
    *res_application = (*storage)->max->application;
    return success;

}

Binomial_Heap_node_ptr find_max(Binomial_Heap_ptr * storage)
{
    Binomial_Heap_node_ptr max = NULL;
    Binomial_Heap_node_ptr current = (*storage)->head;
    while (current)
    {
        if (!max || applications_comparator(max->application, current->application) < 0) max = current;
        current = current->brother;
    }
    return max;
}

status Binomial_Heap_delete_max(Binomial_Heap_ptr * storage, Application_ptr * res_application)
{
   if (Binomial_Heap_get_max(storage, res_application) != success) return invalid_function_argument;

    *res_application = (*storage)->max->application;
    Binomial_Heap_node_ptr max = (*storage)->max;
    Binomial_Heap_node_ptr current = (*storage)->head;
    Binomial_Heap_node_ptr prev = NULL;
    while (current && current != max)
    {
        prev = current;
        current = current->brother;
    }
    // убираем из списка корней
    if (!prev) (*storage)->head = current->brother;
    else prev->brother = max->brother;

    Binomial_Heap_ptr heap = Binomial_Heap_create();
    if (!heap)
    {
        Binomial_Heap_free(storage);
        return no_memory;
    }
    Binomial_Heap_node_ptr node = max->son;
    Binomial_Heap_node_ptr next;
    if (node) next = node->brother;
    else next = NULL;
    Binomial_Heap_node_ptr bro;

    // reverse children
    while (next)
    {
        bro = next->brother;
        next->brother = node;
        node->brother = NULL;
        node = next;
        next = bro;
    }
    heap->head = node;
    Binomial_Heap_ptr new = NULL;
    Binomial_Heap_meld(&new, storage, &heap);
    *storage = new;
    (*storage)->max = find_max(storage);

    free(max);
    max = NULL;

    return success;
}

status Binomial_Heap_insert(Binomial_Heap_ptr * storage, Application_ptr application)
{
    if (!(*storage) || !application)
    {
        Binomial_Heap_free(storage);
        return invalid_function_argument;
    }

    Binomial_Heap_node_ptr node = Binomial_Heap_node_create(application);
    if (!node)
    {
        Binomial_Heap_free(storage);
        return no_memory;
    }

    Binomial_Heap_ptr BH_to_add = Binomial_Heap_create();
    if (!BH_to_add)
    {
        Binomial_Heap_node_free(node);
        Binomial_Heap_free(storage);
        return no_memory;
    }
    BH_to_add->head = node;
    BH_to_add->max = node;
    Binomial_Heap_ptr new = NULL;
    Binomial_Heap_node_ptr max = (*storage) -> max;
    Binomial_Heap_meld(&new, storage, &BH_to_add);
    *storage = new;
    (*storage)->max = max;
    if (!max || (max && applications_comparator(max->application, node->application) < 0)) (*storage)->max = node;

    return success;
}
