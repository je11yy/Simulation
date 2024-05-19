#include "department.h"

#include "../../logger.h"

Operators_work_time_ptr create_work_time(time_t start_time, unsigned int min_handling_time, unsigned int max_handling_time)
{
    Operators_work_time_ptr work_time = (Operators_work_time_ptr)malloc(sizeof(Operators_work_time));
    if (!work_time) return NULL;
    unsigned int handling_time = rand() % (max_handling_time - min_handling_time + 1) + min_handling_time;
    time_t end_time = start_time + (handling_time * 60);
    struct tm * end = localtime(&end_time);
    work_time->start_time = start_time;
    work_time->end_time = end_time;
    work_time->handling_time = handling_time;
    return work_time;
}

char * operator_name_create()
{
    // от 1 до 10
    int length = rand() % 9 + 1;

    char * name = (char*)malloc((length + 1) * sizeof(char));
    if (!name) return NULL;

    name[length] = 0;
    for (int i = 0; i < length; ++i) name[i] = rand() % ('Z' - 'a' + 1) + 'a';
    return name;
}

Operators_ptr operators_list_create()
{
    Operators_ptr operators = (Operators_ptr)malloc(sizeof(Operators));
    if (!operators) return NULL;
    operators->first = NULL;
    operators->size = 0;
    return operators;
}

void operators_list_free(Operators_ptr operators)
{
    if (!operators) return;
    Operator_ptr current = operators->first;
    Operator_ptr next = NULL;
    while (current)
    {
        next = current->next;
        operator_free(current);
        current = next;
    }
    free(operators);
    operators = NULL;
}

Operator_ptr operator_create()
{
    Operator_ptr operator = (Operator_ptr)malloc(sizeof(Operator));
    if (!operator) return NULL;
    operator->work_time = NULL;
    operator->name = operator_name_create();
    operator->application = NULL;
    operator->next = NULL;

    return operator;
}

void operator_free(Operator_ptr operator)
{
    free(operator->name);
    operator->name = NULL;
    free_application(operator->application);
    if (operator->work_time) free(operator->work_time);
    operator->work_time = NULL;
    operator->next = NULL;
    free(operator);
}

Department_ptr department_create(int identifier, application_storage_type applications_storage_type, int operators_count, double overload_coef)
{
    Department_ptr department = (Department_ptr)malloc(sizeof(Department));
    if (!department) return NULL;
    department->identifier = identifier;
    department->applications = application_storage_create(applications_storage_type);
    if (!department->applications)
    {
        free(department);
        return NULL;
    }
    department->overload_coef = overload_coef;
    department->applications_count = 0;

    department->busy_operators = operators_list_create();
    if (!department->busy_operators)
    {
        free(department);
        return NULL;
    }

    department->free_operators = operators_list_create();
    if (!department->free_operators)
    {
        free(department->busy_operators);
        free(department);
        return NULL;
    }

    for (int i = 0; i < operators_count; ++i)
    {
        Operator_ptr new_operator = operator_create();
        if (!new_operator)
        {
            operators_list_free(department->busy_operators);
            operators_list_free(department->free_operators);
            free(department);
            return NULL;
        }
        add_operator_to_list(department->free_operators, new_operator);
    }

    return department;
}

void department_free(Department_ptr department)
{
    if (!department) return;
    operators_list_free(department->busy_operators);
    operators_list_free(department->free_operators);
    application_storage_free(department->applications);
    department->applications = NULL;
    free(department);
    department = NULL;
}

Operator_ptr take_first(Operators_ptr operators)
{
    Operator_ptr operator = operators->first;
    operators->first = operator->next;
    operators->size--;
    return operator;
}

Operator_ptr take_free_operator(Department_ptr * department)
{
    return take_first((*department)->free_operators);
}

Operator_ptr take_busy_operator(Department_ptr * department)
{
    return take_first((*department)->busy_operators);
}

void add_operator_to_list(Operators_ptr operators, Operator_ptr operator)
{
    operator->next = NULL;
    Operator_ptr current = operators->first;
    if (!current)
    {
        operators->first = operator;
        operators->size++;
        return;
    }
    while (current->next) current = current->next;
    current->next = operator;
    operators->size++;
}

status make_busy_operator(Department_ptr * department, Application_ptr application, time_t start_time,
    unsigned int min_handling_time, unsigned int max_handling_time, Logger_ptr logger)
{
    if (*department && !(*department)->free_operators->size) return no_free_operators;
    if (!department || !application) return invalid_function_argument;

    Operator_ptr operator = take_free_operator(department);
    operator->application = application;
    operator->work_time = create_work_time(start_time, min_handling_time, max_handling_time);
    if (!(operator->work_time)) return no_memory;
    add_operator_to_list((*department)->busy_operators, operator);
    // handling application log
    request_handling_started(logger, start_time, application->id, operator->name);

    return success;
}

status compare_time_without_seconds(time_t time1, time_t time2)
{
    struct tm time_info_1;
    localtime_r(&time1, &time_info_1);
    struct tm time_info_2;
    localtime_r(&time2, &time_info_2);
    if (time_info_1.tm_year == time_info_2.tm_year && time_info_1.tm_mon == time_info_2.tm_mon && time_info_1.tm_mday == time_info_2.tm_mday && time_info_1.tm_hour == time_info_2.tm_hour && time_info_1.tm_min == time_info_2.tm_min) return success;
    return fail;
}

status check_busy_operators(Department_ptr * department, time_t current_time, Logger_ptr logger)
{
    if (!*department) return invalid_function_argument;
    if (!(*department)->busy_operators->size) return success;

    Operator_ptr current = (*department)->busy_operators->first;
    Operator_ptr prev = NULL;
    Operator_ptr target = NULL;

    while (current)
    {
        if (compare_time_without_seconds(current_time, current->work_time->end_time) == success)
        {
            target = current;
            if (!prev) (*department)->busy_operators->first = current->next;
            else prev->next = current->next;

            (*department)->busy_operators->size--;
            target->next = NULL;
            add_operator_to_list((*department)->free_operators, target);
            // finished application log
            request_handling_finished(logger, current_time, target->application->id, target->work_time->handling_time, target->name);

            free_application(target->application);
            free(target->work_time);
            target->application = NULL;
            target->work_time = NULL;

        }
        prev = current;
        current = current->next;
    }
    return success;
}

status department_insert_application(Department_ptr department, Application_ptr application)
{
    if (!department || !application) return invalid_function_argument;
    department->applications_count++;
    return department->applications->insert(&department->applications->storage, application);
}