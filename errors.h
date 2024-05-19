#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    success,
    arguments_error,
    no_memory,
    fail,
    invalid_argument,
    file_open_error,
    invalid_info_file,
    invalid_function_argument,
    no_free_operators,
    already_existing_key,
    cannot_find

} status;

void print_help_menu();

void print_error(status const error);

#endif