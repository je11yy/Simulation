#include "BinaryHeap.h"

status Binary_Heap_sift_down(Binary_Heap_ptr * storage, size_t i)
{
    if (!(*storage))
    {
        Binary_Heap_free(storage);
        return invalid_function_argument;
    }

    while (2 * i + 1 < (*storage)->size)
    {
        size_t left_index = 2 * i + 1;
        size_t right_index = 2 * i + 2;
        size_t j = left_index;
        if (right_index < (*storage)->size && applications_comparator((*storage)->elements[right_index], (*storage)->elements[left_index]) > 0) j = right_index;
        if (applications_comparator((*storage)->elements[i], (*storage)->elements[j]) > 0) break;
        Application_ptr tmp = (*storage)->elements[i];
        (*storage)->elements[i] = (*storage)->elements[j];
        (*storage)->elements[j] = tmp;
        i = j;
    }
    return success;
}

status Binary_Heap_sift_up(Binary_Heap_ptr * storage)
{
    if (!(*storage))
    {
        Binary_Heap_free(storage);
        return invalid_function_argument;
    }

    size_t i = (*storage)->size;
    while (i > 0 && applications_comparator((*storage)->elements[(i - 1) / 2], (*storage)->elements[i]) < 0)
    {
        Application_ptr tmp = (*storage)->elements[i];
        (*storage)->elements[i] = (*storage)->elements[(i - 1) / 2];
        (*storage)->elements[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }
    return success;
}

status Binary_Heap_set_null(Binary_Heap_ptr heap)
{
    heap->size = 0;
    heap->capacity = 16;
    heap->elements = NULL;
    return success;
}

Binary_Heap_ptr Binary_Heap_create()
{
    Binary_Heap_ptr heap = (Binary_Heap_ptr)malloc(sizeof(Binary_Heap));
    if (!heap) return NULL;
    heap->size = 0;
    heap->capacity = 16;
    heap->elements = (Application_ptr*)calloc(heap->capacity, sizeof(Application_ptr));
    if (!(heap->elements))
    {
        free(heap);
        return NULL;
    }
    return heap;
}

void Binary_Heap_free(Binary_Heap_ptr * storage)
{
    if (!(*storage)) return;
    if ((*storage)->elements)
    {
        for (int i = 0; i < (*storage)->size; ++i)
        {
            free_application((*storage)->elements[i]);
        }
        free((*storage)->elements);
        (*storage)->elements = NULL;
    }
    free(*storage);
    *storage = NULL;
}

status Binary_Heap_merge(Binary_Heap_ptr * res, Binary_Heap_ptr * first, Binary_Heap_ptr * second)
{
    if (*res || !(*first) || !(*second) || *first == *second)
    {
        Binary_Heap_free(first);
        Binary_Heap_free(second);
        return invalid_function_argument;
    }
    size_t capacity = ((*first)->capacity > (*second)->capacity) ? (*first)->capacity : (*second)->capacity;

    if ((*first)->size + (*second)->size > capacity)
    {
        capacity = ((*first)->size + (*second)->size) * 2;
    }

    Binary_Heap_ptr heap = Binary_Heap_create();
    if (!heap)
    {
        Binary_Heap_free(first);
        Binary_Heap_free(second);
        return no_memory;
    }
    heap->size = (*first)->size + (*second)->size;
    heap->capacity = capacity;
    heap->elements = (Application_ptr *)calloc(capacity, sizeof(Application_ptr));
    if (!(heap->elements))
    {
        free(heap);
        heap = NULL;
        Binary_Heap_free(first);
        Binary_Heap_free(second);
        return no_memory;
    }

    for (size_t i = 0; i < (*first)->size; ++i) heap->elements[i] = copy_application((*first)->elements[i]);
    for (size_t i = 0; i < (*second)->size; ++i) heap->elements[i + (*second)->size] = copy_application((*second)->elements[i]);

    for (size_t i = 0; i < heap->size / 2; ++i) Binary_Heap_sift_down(&heap, heap->size / 2 - i);

    *res = heap;
    return success;
}

status Binary_Heap_meld(Binary_Heap_ptr * res, Binary_Heap_ptr * first, Binary_Heap_ptr * second)
{
    if (*res || !(*first) || !(*second) || *first == *second)
    {
        Binary_Heap_free(first);
        Binary_Heap_free(second);
        return invalid_function_argument;
    }
    size_t capacity = ((*first)->capacity > (*second)->capacity) ? (*first)->capacity : (*second)->capacity;

    if ((*first)->size + (*second)->size > capacity)
    {
        capacity = ((*first)->size + (*second)->size) * 2;
    }

    Binary_Heap_ptr heap = Binary_Heap_create();
    if (!heap)
    {
        Binary_Heap_free(first);
        Binary_Heap_free(second);
        return no_memory;
    }
    heap->size = (*first)->size + (*second)->size;
    heap->capacity = capacity;
    heap->elements = (Application_ptr *)calloc(capacity, sizeof(Application_ptr));
    if (!(heap->elements))
    {
        free(heap);
        heap = NULL;
        Binary_Heap_free(first);
        Binary_Heap_free(second);
        return no_memory;
    }

    for (size_t i = 0; i < (*first)->size; ++i) heap->elements[i] = (*first)->elements[i];
    for (size_t i = 0; i < (*second)->size; ++i) heap->elements[i + (*second)->size] = (*second)->elements[i];

    for (size_t i = 0; i < heap->size / 2; ++i) Binary_Heap_sift_down(&heap, heap->size / 2 - i);

    Binary_Heap_set_null(*first);
    Binary_Heap_free(first);

    Binary_Heap_set_null(*second);
    Binary_Heap_free(second);

    *res = heap;
    return success;
}

status Binary_Heap_get_max(Binary_Heap_ptr * storage, Application_ptr * res_application)
{
    if (!(*storage) || (*res_application))
    {
        Binary_Heap_free(storage);
        return invalid_function_argument;
    }
    *res_application = ((*storage)->elements)[0];
    return success;
}
status Binary_Heap_delete_max(Binary_Heap_ptr * storage, Application_ptr * res_application)
{
    if (Binary_Heap_get_max(storage, res_application) != success) return invalid_function_argument;

    if ((*storage)->size == 0) return success;

    if ((*storage)->size > 1) (*storage)->elements[0] = (*storage)->elements[(*storage)->size - 1];
    else (*storage)->elements[0] = NULL;
    (*storage)->size--;
    Binary_Heap_sift_down(storage, 0);

    return success;
}

status Binary_Heap_insert(Binary_Heap_ptr * storage, Application_ptr application)
{
    if (!(*storage) || !application)
    {
        Binary_Heap_free(storage);
        return invalid_function_argument;
    }

    if ((*storage)->size == (*storage)->capacity)
    {
        (*storage)->capacity *= 2;
        Application_ptr * tmp = (Application_ptr*)realloc((*storage)->elements, sizeof(Application_ptr) * ((*storage)->capacity));
        if (!tmp)
        {
            Binary_Heap_free(storage);
            return no_memory;
        }
        (*storage)->elements = tmp;
    }

    (*storage)->elements[(*storage)->size] = application;
    Binary_Heap_sift_up(storage);
    (*storage)->size++;
    return success;
}
