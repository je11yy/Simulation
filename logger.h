#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <stdio.h>
#include "errors.h"
#include <time.h>

typedef struct Logger
{
    FILE * file;
} Logger, *Logger_ptr;

status create_logger(Logger_ptr * raw_space, FILE * file);

void delete_logger(Logger_ptr logger);

status new_request(Logger_ptr logger, time_t time_log, int appl_id, int dep_id);

status request_handling_started(Logger_ptr logger, time_t time_log, int appl_id, char * name);

status request_handling_finished(Logger_ptr logger, time_t time_log, int appl_id, int handling_time, char * name);

status department_overload(Logger_ptr logger, time_t time_log, int appl_id, int dep_id);
#endif