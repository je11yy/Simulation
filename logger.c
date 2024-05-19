#include "logger.h"

#define MAX_LENGTH 25

status create_logger(Logger_ptr * raw_space, FILE * file)
{
    if (*raw_space) return invalid_argument;
    *raw_space = (Logger_ptr)malloc(sizeof(Logger));
    if (!*raw_space) return no_memory;
    (*raw_space)->file = file;
    return success;
}

void delete_logger(Logger_ptr logger)
{
    fclose(logger->file);
    free(logger);
}

status new_request(Logger_ptr logger, time_t time_log, int appl_id, int dep_id)
{
    if (!logger) return invalid_argument;
    if (!(logger->file)) return invalid_argument;
    char time_str[MAX_LENGTH];
    struct tm* time_tm = localtime(&time_log);
    sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d", 
        time_tm->tm_year+1900, time_tm->tm_mon+1, time_tm->tm_mday, 
            time_tm->tm_hour, time_tm->tm_min, time_tm->tm_sec);

    fprintf(logger->file, "[%s] [%s]: Application id: %d, Department id: %d\n", "NEW_REQUEST", time_str, appl_id, dep_id);
    return success;
}

status request_handling_started(Logger_ptr logger, time_t time_log, int appl_id, char * name)
{
    if (!logger) return invalid_argument;
    if (!(logger->file)) return invalid_argument;
    char time_str[MAX_LENGTH];
    struct tm* time_tm = localtime(&time_log);
    sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d", 
        time_tm->tm_year+1900, time_tm->tm_mon+1, time_tm->tm_mday, 
            time_tm->tm_hour, time_tm->tm_min, time_tm->tm_sec);
    fprintf(logger->file, "[%s] [%s]: Application id: %d, Operator name: %s\n", "REQUEST_HANDLING_STARTED", time_str, appl_id, name);
    return success;
}

status request_handling_finished(Logger_ptr logger, time_t time_log, int appl_id, int handling_time, char * name)
{
    if (!logger) return invalid_argument;
    if (!(logger->file)) return invalid_argument;
    char time_str[MAX_LENGTH];
    struct tm* time_tm = localtime(&time_log);
    sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d", 
        time_tm->tm_year+1900, time_tm->tm_mon+1, time_tm->tm_mday, 
            time_tm->tm_hour, time_tm->tm_min, time_tm->tm_sec);
    fprintf(logger->file, "[%s] [%s]: Application id: %d, Handling time: %d, Operator name: %s\n", "REQUEST_HANDLING_FINISHED", time_str, appl_id, handling_time, name);
    return success;
}

status department_overload(Logger_ptr logger, time_t time_log, int appl_id, int dep_id)
{
    if (!logger) return invalid_argument;
    if (!(logger->file)) return invalid_argument;
    char time_str[MAX_LENGTH];
    struct tm* time_tm = localtime(&time_log);
    sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d", 
        time_tm->tm_year+1900, time_tm->tm_mon+1, time_tm->tm_mday, 
            time_tm->tm_hour, time_tm->tm_min, time_tm->tm_sec);
    fprintf(logger->file, "[%s] [%s]: Application id: %d, New department id: %d\n", "DEPARTMENT_OVERLOAD", time_str, appl_id, dep_id);
    return success;
}