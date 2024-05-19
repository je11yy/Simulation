#ifndef _APPLICATION_
#define _APPLICATION_

#include <time.h>
#include "errors.h"

typedef struct Application
{
    time_t time;
    unsigned int priority;
    char * text;
    int id;
    int department_id;
    
} Application, * Application_ptr;

Application_ptr new_application(
    time_t time, unsigned int priority, char * text, int id, int depart_id);

void free_application(Application_ptr application);

int applications_comparator(Application_ptr first, Application_ptr second);

Application_ptr copy_application(Application_ptr application);

#endif