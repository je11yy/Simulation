#include "validation.h"
#include "storages/application_storage.h"
#include "storages/department_storage.h"

#define _GNU_SOURCE

status unsigned_int_check(char * number)
{
    if (number[strlen(number) - 1] == '\n') number[strlen(number) - 1] = 0;
    size_t i = 0;
    while(number[i] != '\0') if (!isdigit(number[i++])) return fail;
    return success;
}

status double_check(char * number)
{
    if (number[strlen(number) - 1] == '\n') number[strlen(number) - 1] = 0;
    size_t cur = 0;
    if (strcmp(number, "-") == success) return fail;
    while (*number != 0)
    {
        if (*number == '.')
        {
            if (cur == 0) cur += 1;
            else return fail;
        }
        else if (!isdigit(*number)) return fail;
        number++;
    }
    return success;
}

status validate_storage_structure(char * string, application_storage_type * structure)
{
    if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = 0;
    size_t storages_types_count = 6;
    const char * storages_types[] = 
    {
        "BinaryHeap",
        "BinomialHeap",
        "FibonacciHeap",
        "SkewHeap",
        "LeftistHeap",
        "Treap"
    };
    for (size_t i = 0; i < storages_types_count; ++i)
    {
        if (strcmp(storages_types[i], string) == success)
        {
            *structure = i;
            return success;
        }
    }
    return fail;
}

status validate_departments_structure(char * string, department_type * structure)
{
    if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = 0;
    size_t department_types_count = 4;
    const char * departments_types[] = 
    {
        "HashSet",
        "DynamicArray",
        "BinarySearchTree",
        "Trie"
    };
    for (size_t i = 0; i < department_types_count; ++i)
    {
        if (strcmp(departments_types[i], string) == success)
        {
            *structure = i;
            return success;
        }
    }
    return fail;
}

status is_leap_year(const int year)
{
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) return success;
    return fail;
}

status validate_time(char * time)
{
    if (time[strlen(time) - 1] == '\n') time[strlen(time) - 1] = 0;
    const char * time_format = "YYYY-MM-DD hh:mm:ss";
    int year, month, day, hour, minute, second;
    if (sscanf(time, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) < 0) return fail;

    if (month < 1 || month > 12) return fail;
    if (day < 1 || day > 31) return fail;

    if (month == 2)
    {
        status result = is_leap_year(year);
        if (result == success && day > 29) return fail;
        else if (result != success && day > 28) return fail;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30) return fail;
    }
    return success;
}

status validate_structures(FILE * file, application_storage_type * applications_storage, department_type * departments_storage)
{
    char * line = NULL;
    size_t size = 0;

    // вид структуры для заявок
    if (getline(&line, &size, file) < 0 || validate_storage_structure(line, applications_storage) != success)
    {
        free(line);
        fclose(file);
        return arguments_error;
    }
    free(line);
    line = NULL;
    size = 0;
    // вид структуры для отделений
    if (getline(&line, &size, file) < 0 || validate_departments_structure(line, departments_storage) != success)
    {
        free(line);
        fclose(file);
        return arguments_error;
    }
    free(line);
    line = NULL;
    size = 0;
    return success;
}

status validate_start_and_end(FILE * file, time_t * time_1)
{
    char * line = NULL;
    size_t size = 0;
    if (getline(&line, &size, file) < 0 || validate_time(line) != success)
    {
        free(line);
        fclose(file);
        return arguments_error;
    }
    struct tm tm_1 = {};
    strptime(line, "%Y-%m-%d %H:%M:%S", &tm_1);
    time_t cur_time = mktime(&tm_1);
    *time_1 = cur_time;
    free(line);
    line = NULL;
    size = 0;
    return success;
}

status validate_application_time_and_departments_count(FILE * file, int * argument)
{
    char * line = NULL;
    size_t size = 0;

    if (getline(&line, &size, file) < 0 || unsigned_int_check(line) != success)
    {
        free(line);
        fclose(file);
        return arguments_error;
    }
    sscanf(line, "%d", argument);
    
    free(line);
    line = NULL;
    size = 0;
    return success;
}