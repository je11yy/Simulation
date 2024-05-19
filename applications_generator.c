#include <stdio.h>
#include <time.h>

#include "errors.h"

#define MAX_PRIORITY 10

#define MAX_APPLICATIONS_COUNT 100
#define MAX_YEAR 2024
#define MIN_YEAR 2024
#define MAX_MONTH 4
#define MIN_MONTH 4
#define MAX_DAY 25
#define MIN_DAY 25
#define MAX_HOUR 13
#define MIN_HOUR 12
#define MAX_MIN 59
#define MAX_SEC 59
#define MAX_MESSAGE_LENGTH 100
#define MAX_ID 100000
#define MAX_DEP_ID 5
#define MIN_DEP_ID 1

int generate_applications_count()
{
    return 1 + rand() % MAX_APPLICATIONS_COUNT;
}

status is_leap_year(const int year)
{
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) return success;
    return fail;
}

void generate_time(int * year, int * month, int * day, int * hour, int * min, int * sec)
{
    *year = MIN_YEAR + rand() % (MAX_YEAR - MIN_YEAR + 1);
    *month = MIN_MONTH + rand() % (MAX_MONTH - MIN_MONTH + 1);
    *day = MIN_DAY + rand() % (MAX_DAY - MIN_DAY + 1);
    *hour = MIN_HOUR + rand() % (MAX_HOUR - MIN_HOUR + 1);
    *min = 1 + rand() % MAX_MIN;
    *sec = 1 + rand() % MAX_SEC;
}

int generate_priority()
{
    return rand() % (MAX_PRIORITY + 1);
}

int generate_identificator()
{
    return 1 + rand() % MAX_ID;
}

int generate_dep_id()
{
    return MIN_DEP_ID + rand() % (MAX_DEP_ID - MIN_DEP_ID + 1);
}

char * generate_message()
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:'\",.<>/?";
    int charset_length = sizeof(charset) - 1; 

    int length = 1 + rand() % MAX_MESSAGE_LENGTH;
    char * message = (char*)malloc((length + 1) * sizeof(char));
    if (!message) return NULL;
    for (int i = 0; i < length; ++i) message[i] = charset[rand() % (charset_length)];
    message[length] = 0;
    return message;
}

int main(int argc, char * argv[])
{
    FILE * file;
    if (argc == 1)
    {
        file = fopen("applications.txt", "w");
        if (!file)
        {
            print_error(file_open_error);
            return file_open_error;
        }
    }
    else if (argc == 2)
    {
        file = fopen(argv[1], "w");
        if (!file)
        {
            print_error(file_open_error);
            return file_open_error;
        }
    }
    else 
    {
        print_error(invalid_argument);
        return invalid_argument;
    }
    srand(time(NULL));
    int count = generate_applications_count();
    for (int i = 0; i < count; ++i)
    {
        int year, mon, day, hour, min, sec;
        generate_time(&year, &mon, &day, &hour, &min, &sec);
        fprintf(file, "%04d-%02d-%02d %02d:%02d:%02d ", year, mon, day, hour, min, sec);
        fprintf(file, "%d ", generate_priority());
        fprintf(file, "%d %d ", generate_dep_id(), generate_identificator());
        char * message = generate_message();
        if (!message)
        {
            fclose(file);
            print_error(no_memory);
            return no_memory;
        }
        fprintf(file, "\"%s\"", message);
        free(message);
        message = NULL;
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Applications has been generated\n");
    return success;
}