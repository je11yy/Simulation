#ifndef _APLLICATION_STORAGE_H_
#define _APLLICATION_STORAGE_H_

#include "../errors.h"
#include "../application.h"
#include "applications/BinaryHeap.h"
#include "applications/BinomialHeap.h"
#include "applications/FibonacciHeap.h"
#include "applications/LeftistHeap.h"
#include "applications/SkewHeap.h"
#include "applications/Treap.h"

typedef enum
{
    BinaryHeap_T = 0,
    BinomialHeap_T = 1,
    FibonacciHeap_T = 2,
    SkewHeap_T = 3,
    LeftistHeap_T = 4,
    Treap_T = 5
} application_storage_type;

typedef struct Application_storage
{
    void * storage;
    application_storage_type type;

    status (*insert) (void ** storage, Application_ptr application);
    void (*free) (void ** storage);
    status (*get_max) (void ** storage, Application_ptr * res_application);
    status (*delete_max) (void ** storage, Application_ptr * res_application);
    status (*merge) (void ** res_storage, void ** first, void ** second);
    status (*meld) (void ** res_storage, void ** first, void ** second);
    status (*set_null) (void * storage);

} Application_storage, *Application_storage_ptr;

Application_storage_ptr application_storage_create(application_storage_type type);
void application_storage_free(Application_storage_ptr storage);
void application_storage_take_application(Application_storage_ptr storage, Application_ptr * appl);

#endif