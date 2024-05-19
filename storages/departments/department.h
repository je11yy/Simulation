#ifndef _DEPARTMENT_H
#define _DEPARTMENT_H

#include "../application_storage.h"
#include "../../logger.h"

typedef struct Operators_work_time
{
    time_t start_time;
    time_t end_time;
    int handling_time;

} Operators_work_time, *Operators_work_time_ptr;

typedef struct Operator
{
    char * name;
    
    Application_ptr application;
    Operators_work_time_ptr work_time;

    struct Operator * next;

} Operator, *Operator_ptr;

typedef struct Operators
{
    Operator_ptr first;
    size_t size;

} Operators, *Operators_ptr;

typedef struct Department
{
    int identifier;
    Application_storage_ptr applications;
    size_t applications_count;

    Operators_ptr busy_operators;

    Operators_ptr free_operators;

    double overload_coef;

} Department, *Department_ptr;

Operators_work_time_ptr create_work_time(time_t start_time, unsigned int min_handling_time, unsigned int max_handling_time);

char * operator_name_create();

Operators_ptr operators_list_create();
void operators_list_free(Operators_ptr operators);

Operator_ptr operator_create();
void operator_free(Operator_ptr operator);

Department_ptr department_create(int identifier, application_storage_type applications_storage_type, int operators_count, double overload_coef);
void department_free(Department_ptr department);

Operator_ptr take_first(Operators_ptr operators);
Operator_ptr take_free_operator(Department_ptr * department);
Operator_ptr take_busy_operator(Department_ptr * department);
void add_operator_to_list(Operators_ptr operators, Operator_ptr operator);
status make_busy_operator(Department_ptr * department, Application_ptr application, time_t start_time,
    unsigned int min_handling_time, unsigned int max_handling_time, Logger_ptr logger);
status check_busy_operators(Department_ptr * department, time_t current_time, Logger_ptr logger);

status department_insert_application(Department_ptr department, Application_ptr application);

status compare_time_without_seconds(time_t time1, time_t time2);

#endif