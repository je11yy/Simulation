#ifndef _VALIDATION_H_
#define _VALIDATION_H_

#define _GNU_SOURCE
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "errors.h"
#include "string.h"
#include "storages/application_storage.h"
#include "storages/department_storage.h"

status unsigned_int_check(char * number);

status double_check(char * number);

status validate_storage_structure(char * string, application_storage_type * structure);

status validate_departments_structure(char * string, department_type * structure);

status is_leap_year(const int year);

status validate_time(char * time);

status validate_application_time_and_departments_count(FILE * file, int * argument);

status validate_start_and_end(FILE * file, time_t * time_1);

status validate_structures(FILE * file, application_storage_type * applications_storage, department_type * departments_storage);

#endif