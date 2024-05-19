#include "errors.h"

void print_error(status const error)
{
    const char * main_error = "[ERROR]";
    const char * errors[] = 
    {
        "Incorrect arguments.",
        "Memory error.",
        "File open error.",
        "Invalid info file.",
        "Invalid function argument.",
        "No free operators.",
        "Already existing key.",
        "Cannot find."
    };
    switch (error)
    {
        case arguments_error:
            printf("%s %s\n", main_error, errors[0]);
            break;
        case no_memory:
            printf("%s %s\n", main_error, errors[1]);
            break;
        case file_open_error:
            printf("%s %s\n", main_error, errors[2]);
            break;
        case invalid_info_file:
            printf("%s %s\n", main_error, errors[3]);
            break;
        case invalid_function_argument:
            printf("%s %s\n", main_error, errors[4]);
            break;
        case no_free_operators:
            printf("%s %s\n", main_error, errors[5]);
            break;
        case already_existing_key:
            printf("%s %s\n", main_error, errors[6]);
            break;
        case cannot_find:
            printf("%s %s\n", main_error, errors[7]);
            break;
        
        default: break;
    }
}