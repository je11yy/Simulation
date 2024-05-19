#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "validation.h"
#include <string.h>
#include "logger.h"

#include "storages/application_storage.h"
#include "storages/department_storage.h"

#include "application.h"

status info_file_check(FILE * info_file, application_storage_type * applications_storage, department_type * departments_storage, time_t * start_time, time_t * end_time, 
    unsigned int * min_application_time, unsigned int * max_application_time, int * departments_count, int ** departments_id_array, int ** departments_workers_count_array, 
    double * overload_coef)
{
    if (validate_structures(info_file, applications_storage, departments_storage) != success) return arguments_error;

    // начало моделирования
    if (validate_start_and_end(info_file, start_time) != success) return arguments_error;
    
    // конец моделирования
    if (validate_start_and_end(info_file, end_time) != success) return arguments_error;

    // время конца должно быть больше времени начала
    if (difftime(*start_time, *end_time) > 0)
    {
        fclose(info_file);
        return arguments_error;
    }

    // минимальное время обработки оператором
    if (validate_application_time_and_departments_count(info_file, min_application_time) != success) return arguments_error;

    // максимальное время обработки оператором
    if (validate_application_time_and_departments_count(info_file, max_application_time) != success) return arguments_error;

    // количество отделений
    if (validate_application_time_and_departments_count(info_file, departments_count) != success) return arguments_error;

    if ((*departments_count) < 1 || (*departments_count) > 100)
    {
        fclose(info_file);
        return arguments_error;
    }

    *departments_workers_count_array = (int*)malloc((*departments_count) * sizeof(int));
    if (!(*departments_workers_count_array))
    {
        fclose(info_file);
        return no_memory;
    }

    *departments_id_array = (int*)malloc((*departments_count) * sizeof(int));
    if (!(*departments_id_array))
    {
        free(*departments_workers_count_array);
        fclose(info_file);
        return no_memory;
    }

    // для каждого отделения: идентификатор
    for (int i = 0; i < *departments_count; ++i)
    {
        int res;
        if (fscanf(info_file, "%d", &res) < 0 || res < 0)
        {
            printf("%d\n", res);
            free(*departments_id_array);
            free(*departments_workers_count_array);
            fclose(info_file);
            return arguments_error;
        }
        ((*departments_id_array)[i]) = res;
    }

    // для каждого отделения: количество операторов
    for (int i = 0; i < *departments_count; ++i)
    {
        int res;
        if (fscanf(info_file, "%d", &res) < 0 || res < 10 || res > 50)
        {
            free(*departments_id_array);
            free(*departments_workers_count_array);
            fclose(info_file);
            return arguments_error;
        }
        ((*departments_workers_count_array)[i]) = res;
    }
    
    // коэффициент перегрузки
    if (fscanf(info_file, "%lf", overload_coef) < 0 || (*overload_coef) < 1.0)
    {
        free(*departments_id_array);
        free(*departments_workers_count_array);
        fclose(info_file);
        return arguments_error;
    }
    fclose(info_file);
    return success;
}


status add_application_to_array(Application_ptr application, Application_ptr ** array, size_t * size, size_t * capacity)
{
    if (*capacity == 0)
    {
        *capacity = 4;
        *array = (Application_ptr *)calloc(*capacity, sizeof(Application_ptr));
        if (!*array) return no_memory;
    }
    else if (*capacity == *size)
    {
        *capacity *= 2;
        Application_ptr * tmp = (Application_ptr *)realloc(*array, (*capacity) * sizeof(Application_ptr));
        if (!tmp)
        {
            free(*array);
            return no_memory;
        }
        *array = tmp;
    }
    int index = *size;
    Application_ptr tmp = NULL;

    // поиск места (от меньшего времени к большему)
    for (int i = 0; i < *size; ++i)
    {
        if ((*array)[i]->time > application->time)
        {
            // сдвиг
            index = i;
            for (int j = (*size); j > i; --j)
            {
                (*array)[j] = (*array)[j - 1];
            }
            break;
        }
    }
    (*array)[index] = application;
    (*size)++;
    return success;
}

status scan_applications(Application_ptr ** array, size_t * size, size_t * capacity, FILE * file, int max_priority)
{
    char * line = NULL;
    size_t length = 0;
    while (!feof(file) && getline(&line, &length, file) > 0)
    {
        // date and time
        if (validate_time(line) != success)
        {
            free(line);
            fclose(file);
            return arguments_error;
        }
        struct tm appl_time = {};
        strptime(line, "%Y-%m-%d %H:%M:%S", &appl_time);
        time_t application_time = mktime(&appl_time);
        char * token = strtok(line, " ");
        if (!token) return arguments_error;
        token = strtok(NULL, " ");
        if (!token) return arguments_error;

        // priority
        token = strtok(NULL, " ");
        if (!token) return arguments_error;
        if (unsigned_int_check(token) != success)
        {
            free(line);
            fclose(file);
            return arguments_error;
        }
        int priority;
        sscanf(token, "%d", &priority);
        if (priority > max_priority)
        {
            free(line);
            fclose(file);
            return arguments_error;
        }

        
        // department identificator
        token = strtok(NULL, " ");
        if (!token) return arguments_error;
        if (unsigned_int_check(token) != success)
        {
            free(line);
            fclose(file);
            return arguments_error;
        }
        int department_identificator;
        sscanf(token, "%d", &department_identificator);

        // application identificator
        token = strtok(NULL, " ");
        if (!token) return arguments_error;
        if (unsigned_int_check(token) != success)
        {
            free(line);
            fclose(file);
            return arguments_error;
        }
        int application_id;
        sscanf(token, "%d", &application_id);

        // message
        token = strtok(NULL, " ");
        if (!token) return arguments_error;
        if (token[strlen(token) - 1] == '\n') token[strlen(token) - 1] = 0;
        if (token[0] != token[strlen(token) - 1] && token[0] != '\"')
        {
            free(line);
            fclose(file);
            return arguments_error;
        }
        // creating application
        Application_ptr application = new_application(application_time, priority, token, application_id, department_identificator);
        if (!application)
        {
            free(line);
            fclose(file);
            return arguments_error;
        }
        if (add_application_to_array(application, array, size, capacity) != success)
        {
            free(line);
            fclose(file);
            return arguments_error;
        }

        free(line);
        line = NULL;
        length = 0;
    }
    free(line);
    line = NULL;
    fclose(file);
    return success;
}

Application_ptr take_cur_time_application(Application_ptr * applications, size_t * size, time_t current_time)
{
    if (!(*size)) return NULL;
    if (compare_time_without_seconds(current_time, applications[0]->time) == success)
    {
        Application_ptr application = applications[0];
        for (int j = 0; j < *size; ++j) applications[j] = applications[j + 1];
        (*size)--;
        applications[*size] = NULL;
        return application;
    }
    return NULL;
}

status check_overloading(Department_storage_ptr departments, int * departments_id_array, int departments_count, Logger_ptr logger, time_t current_time, int last_appl_id)
{
    for (int i = 0; i < departments_count; ++i)
    {
        status error;
        Department_ptr dep = NULL;
        if ((error = departments->find(departments->storage, departments_id_array[i], &dep)) != success) return error;
        size_t operators = dep->busy_operators->size + dep->free_operators->size;
        size_t applications = dep->applications_count;

        double eps = 0.000000001;

        double ovrl_coef = applications/operators;

        if (ovrl_coef < dep->overload_coef) continue;

        Department_ptr min_overload_department = NULL;
        double min_ovrl_coef = -1;

        for (int j = 0; j < departments_count; ++j)
        {
            if (departments_id_array[j] == dep->identifier) continue;
            Department_ptr current_department = NULL;
            if ((error = departments->find(departments->storage, departments_id_array[j], &current_department)) != success) return error;

            size_t cur_operators = current_department->busy_operators->size + current_department->free_operators->size;
            size_t cur_applications = current_department->applications_count;

            if (!min_overload_department || cur_applications/cur_operators - min_ovrl_coef < eps)
            {
                min_overload_department = current_department;
                min_ovrl_coef = cur_applications/cur_operators;
            }
        }
        void * new = NULL;
        if ((error = dep->applications->meld(&new, &min_overload_department->applications->storage, &dep->applications->storage)) != success) return error;
        
        min_overload_department->applications->storage = new;
        dep->applications = NULL;
        free(dep->applications);
        dep->applications = application_storage_create(min_overload_department->applications->type);
        if (!dep->applications) return no_memory;
        dep->applications_count = 0;
        department_overload(logger, current_time, last_appl_id, min_overload_department->identifier);
    }

    return success;
}

status vacation_for_finished_operators(Department_storage_ptr departments, time_t current_time, int * departments_id_array, int departments_count, Logger_ptr logger)
{
    for (int i = 0; i < departments_count; ++i)
    {
        Department_ptr current_department = NULL;
        status error;
        if ((error = departments->find(departments->storage, departments_id_array[i], &current_department)) != success) return error;
        if ((error = check_busy_operators(&current_department, current_time, logger)) != success) return error;
    }
    return success;
}

status make_all_free_operators_busy(Department_storage_ptr departments, int * departments_id_array, int departments_count, time_t current_time, unsigned int min_handling_time, unsigned int max_handling_time, Logger_ptr logger)
{
    for (int i = 0; i < departments_count; ++i)
    {
        Department_ptr current_department = NULL;
        status error;
        if ((error = departments->find(departments->storage, departments_id_array[i], &current_department)) != success) return error;
        while (current_department->free_operators->size && current_department->applications_count)
        {
            if (!current_department->applications_count) break;
            Application_ptr application = NULL;

            current_department->applications->delete_max(&(current_department->applications->storage), &application);

            current_department->applications_count--;
            if ((error = make_busy_operator(&current_department, application, current_time, min_handling_time, max_handling_time, logger)) != success) return error;
        }
    }
    return success;
}

void print_departments_data(Department_storage_ptr departments, int * departments_id_array, int departments_count)
{
    for (int i = 0; i < departments_count; ++i)
    {
        Department_ptr current_department = NULL;
        status error;
        if ((error = departments->find(departments->storage, departments_id_array[i], &current_department)) != success) return;
        printf("%d %ld %ld %ld\n", current_department->identifier, current_department->applications_count, current_department->busy_operators->size, current_department->free_operators->size);
    }
    printf("__________________\n");
}

status simulating(Logger_ptr logger, Department_storage_ptr departments, Application_ptr * applications, size_t * size, time_t starting_time, time_t ending_time, int * departments_id_array, int departments_count, unsigned int min_handling_time, unsigned int max_handling_time)
{
    double seconds = 60;
    while (starting_time < ending_time)
    {
        status error;
        // извлечение заявок с текущим временем
        struct tm time_info_1;
        localtime_r(&starting_time, &time_info_1);
        int last_id = -1;
        Application_ptr current_application = take_cur_time_application(applications, size, starting_time);
        while (current_application)
        {
            last_id = current_application->id;
            // new request log
            new_request(logger, starting_time, current_application->id, current_application->department_id);
            if ((error = departments_storage_insert_application(departments, current_application)) != success) return error;
            current_application = take_cur_time_application(applications, size, starting_time);
        }
        // проверка на загруженность отделений
        if ((error = check_overloading(departments, departments_id_array, departments_count, logger, starting_time, last_id)) != success) return error;
        
        // разгрузка операторов, закончивших работу
        if ((error = vacation_for_finished_operators(departments, starting_time, departments_id_array, departments_count, logger)) != success) return error;

        // загрузка операторов заявками
        if ((error = make_all_free_operators_busy(departments, departments_id_array, departments_count, starting_time, min_handling_time, max_handling_time, logger)) != success) return error;

        starting_time += seconds;
    }
    return success;
}

int main(int argc, char * argv[])
{
    unsigned int max_priority;
    if (argc < 3 || unsigned_int_check(argv[1]) != success)
    {
        print_error(arguments_error);
        return arguments_error;
    }
    sscanf(argv[1], "%ud", &max_priority);
    FILE * info_file = fopen(argv[2], "r");
    if (!info_file)
    {
        print_error(file_open_error);
        return file_open_error;
    }

    application_storage_type applications_storage;
    department_type departments_storage;
    time_t start_time, end_time;
    unsigned int min_application_time, max_application_time;
    int departments_count;
    int * departments_workers_array = NULL;
    int * departments_id_array = NULL;
    double overload_coef;
    
    status error = info_file_check(info_file, &applications_storage, &departments_storage, &start_time, &end_time,
        &min_application_time, &max_application_time, &departments_count, &departments_id_array, &departments_workers_array, &overload_coef);
    if (error != success)
    {
        print_error(error);
        return error;
    }


    // creating of departments storage
    Department_storage_ptr department_storage = department_storage_create(departments_storage);
    if (!department_storage)
    {
        free(departments_workers_array);
        free(departments_id_array);
        print_error(no_memory);
        return no_memory;
    } 

    // creating of departments
    for (int i = 0; i < departments_count; ++i)
    {
        Department_ptr new_dep = department_create(departments_id_array[i], applications_storage, departments_workers_array[i], overload_coef);
        if (!new_dep)
        {
            free(departments_workers_array);
            department_storage->free(department_storage->storage);
            free(department_storage);
            free(departments_id_array);
            print_error(no_memory);
            return no_memory;
        }
        if ((error = department_storage->insert(department_storage->storage, departments_id_array[i], new_dep)) != success)
        {
            department_free(new_dep);
            new_dep = NULL;
            free(departments_workers_array);
            department_storage->free(department_storage->storage);
            free(department_storage);
            free(departments_id_array);
            print_error(error);
            return error;
        }
    }
    free(departments_workers_array);
    departments_workers_array = NULL;

    // scanning applications
    Application_ptr * applications_array = NULL;
    size_t size = 0;
    size_t capacity = 0;
    for (int i = 3; i < argc; ++i)
    {
        FILE * application_file = fopen(argv[i], "r");
        if (!application_file)
        {
            department_storage->free(department_storage->storage);
            free(department_storage);
            free(departments_id_array);
            print_error(file_open_error);
            return file_open_error;
        }
        if ((error = scan_applications(&applications_array, &size, &capacity, application_file, max_priority)) != success)
        {
            department_storage->free(department_storage->storage);
            free(department_storage);
            free(departments_id_array);
            print_error(error);
            return error;
        }
    }

    // for (int i = 0; i < size; ++i) printf("%d %d\n", applications_array[i]->priority, applications_array[i]->id);

    // creating logger
    Logger_ptr logger = NULL;
    FILE * log_file = fopen("simulation_logging.txt", "w");
    if (create_logger(&logger, log_file) != success)
    {
        department_storage->free(department_storage->storage);
        free(department_storage);
        free(departments_id_array);
        print_error(no_memory);
        return no_memory;
    }

    // simulating
    if ((error = simulating(logger, department_storage, applications_array, &size, start_time, end_time, departments_id_array, departments_count, min_application_time, max_application_time)) != success)
    {
        delete_logger(logger);
        department_storage->free(department_storage->storage);
        free(department_storage);
        free(departments_id_array);
        print_error(error);
        return error;
    }

    for (int i = 0; i < size; ++i) free_application(applications_array[i]);
    free(applications_array);

    delete_logger(logger);
    free(departments_id_array);
    department_storage->free(department_storage->storage);
    free(department_storage);

    printf("Program has finished succesfully\n");

    return success;
}