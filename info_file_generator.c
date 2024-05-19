#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include "validation.h"

int main()
{
    char * write_down = "\n\n>> Write down your answer: ";
    char * wrong = "\nSomething went wrong.\n>> Try again: ";

    size_t application_storages_types_count = 6;
    const char * application_storages_types[] = 
    {
        "BinaryHeap",
        "BinomialHeap",
        "FibonacciHeap",
        "SkewHeap",
        "LeftistHeap",
        "Treap"
    };
    size_t department_types_count = 4;
    const char * departments_types[] = 
    {
        "HashSet",
        "DynamicArray",
        "BinarySearchTree",
        "Trie"
    };

    printf("Welcome to the info file generator! Lets generate file together <3\n");


    printf("\nWhat structure you want to use for applications storage?\nYou can choose: ");
    for (int i = 0; i < application_storages_types_count; ++i) printf("%s ", application_storages_types[i]);

    FILE * console = fopen("/dev/tty", "r");
    if (!console) return file_open_error;
    FILE * info_file = fopen("info.txt", "w");
    if (!info_file) return file_open_error;

    printf("%s", write_down);
    char * line = NULL;
    size_t size = 0;
    application_storage_type applications_type;
    while (getline(&line, &size, console) < 0 || validate_storage_structure(line, &applications_type) != success) printf("%s", wrong);
    fprintf(info_file, "%s\n", application_storages_types[applications_type]);

    printf("\nWhat structure you want to use for departments storage?\nYou can choose: ");
    for (int i = 0; i < department_types_count; ++i) printf("%s ", departments_types[i]);

    printf("%s", write_down);
    line = NULL;
    size = 0;
    department_type departments_type;
    while (getline(&line, &size, console) < 0 || validate_departments_structure(line, &departments_type) != success) printf("%s", wrong);
    fprintf(info_file, "%s\n", departments_types[departments_type]);

    printf("\nWhat will be the start modeling time?\n");
    printf("%s", write_down);
    line = NULL;
    size = 0;
    while (getline(&line, &size, console) < 0 || validate_time(line) != success) printf("%s", wrong);
    fprintf(info_file, "%s\n", line);

    printf("\nWhat will be the end modeling time?\n");
    printf("%s", write_down);
    line = NULL;
    size = 0;
    while (getline(&line, &size, console) < 0 || validate_time(line) != success) printf("%s", wrong);
    fprintf(info_file, "%s\n", line);

    printf("\nWhat will be the min handling time (in minutes)?\n");
    printf("%s", write_down);
    line = NULL;
    size = 0;
    while (getline(&line, &size, console) < 0 || unsigned_int_check(line) != success) printf("%s", wrong);
    fprintf(info_file, "%s\n", line);

    printf("\nWhat will be the max handling time (in minutes)?\n");
    printf("%s", write_down);
    line = NULL;
    size = 0;
    while (getline(&line, &size, console) < 0 || unsigned_int_check(line) != success) printf("%s", wrong);
    fprintf(info_file, "%s\n", line);

    printf("\nWhat will be departments count?\n");
    printf("%s", write_down);
    line = NULL;
    size = 0;
    while (getline(&line, &size, console) < 0 || unsigned_int_check(line) != success) printf("%s", wrong);
    fprintf(info_file, "%s\n", line);

    printf("\nNow, write down for every department its id\n");
    printf("%s", write_down);
    int dep_count;
    sscanf(line, "%d", &dep_count);
    for (int i = 0; i < dep_count; ++i)
    {
        int id;
        while (scanf("%d", &id) < 0 || id < 0) printf("%s", wrong);
        fprintf(info_file, "%d ", id);
    }
    fprintf(info_file, "\n");

    printf("\nWrite down for every department its operators count\n");
    printf("%s", write_down);
    for (int i = 0; i < dep_count; ++i)
    {
        int count;
        while (scanf("%d", &count) < 0 || count < 0) printf("%s", wrong);
        fprintf(info_file, "%d ", count);
    }

    fprintf(info_file, "\n");

    printf("\nWhat will be the overload coef?\n");
    printf("%s", write_down);
    line = NULL;
    size = 0;
    while (getline(&line, &size, console) < 0 || double_check(line) != success) printf("%s", wrong);
    fprintf(info_file, "%s\n", line);

    free(line);
    fclose(console);
    fclose(info_file);

    printf("\n\nSession finished.\n");
    return success;
}