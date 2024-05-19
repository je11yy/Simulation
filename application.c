#include "application.h"
#include "errors.h"
#include "string.h"

Application_ptr new_application(
    time_t time, unsigned int priority, char * text, int id, int depart_id)
{
    Application_ptr application = (Application_ptr)malloc(sizeof(Application));
    if (!application) return NULL;
    application->time = time;
    application->priority = priority;
    application->text = (char*)calloc(strlen(text), sizeof(char));
    if (!(application->text))
    {
        free(application);
        return NULL;
    }
    memcpy(application->text, text, strlen(text));
    application->id = id;
    application->department_id = depart_id;
    return application;
}

void free_application(Application_ptr application)
{
    if (!application) return;
    if (application->text)
    {
        free(application->text);
        application->text = NULL;
    }
    free(application);
    application = NULL;
}

int applications_comparator(Application_ptr first, Application_ptr second)
{
    if (!first || !second) return invalid_function_argument;
    if (first->priority != second->priority) return (first->priority) - (second->priority);
    double dif = difftime(first->time, second->time);
    if (dif > 0) return 1;
    else if (dif < 0) return -1;
    return 0;
}

Application_ptr copy_application(Application_ptr application)
{
    Application_ptr copy = (Application_ptr)malloc(sizeof(Application));
    if (!copy) return NULL;
    int size = strlen(application->text);
    copy->text = (char*)malloc(size * sizeof(char));
    if (!(copy->text))
    {
        free(copy);
        free_application(application);
        return NULL;
    }
    memcpy(copy->text, application->text, size);
    copy->department_id = application->department_id;
    copy->priority = application->priority;
    copy->id = application->id;
    return copy;
}
