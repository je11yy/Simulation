#include "BinaryHeap.h"
#include "BinomialHeap.h"
#include "FibonacciHeap.h"
#include "LeftistHeap.h"
#include "../../application.h"
#include "SkewHeap.h"
#include "Treap.h"

char * result[] = {"[PASSED]\n", "[FAILED]"};

void Binary_Heap_test()
{
    char * name = "[BINARY HEAP TEST]";
    Binary_Heap_ptr heap = Binary_Heap_create();
    if (!heap)
    {
        printf("%s %s NO_MEMORY HEAP\n", name, result[1]);
        return;
    }

    Application_ptr application_1 = new_application(time(NULL), 10, "aaaasksks", 1, 12);
    if (!application_1)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_2 = new_application(time(NULL), 9, "aaaasamfksks", 2, 24);
    if (!application_2)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_3 = new_application(time(NULL), 4, "kfW", 6, 2);
    if (!application_3)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    if (Binary_Heap_insert(&heap, application_1) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    if (Binary_Heap_insert(&heap, application_2) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    if (Binary_Heap_insert(&heap, application_3) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }

    Application_ptr appl_result = NULL;

    if (Binary_Heap_get_max(&heap, &appl_result) != success)
    {
        printf("%s %s GET_MAX\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    appl_result = NULL;

    if (Binary_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 1\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s NOT MAX %d \n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    appl_result = NULL;

    if (Binary_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 2\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 9)
    {
        printf("%s %s NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    Binary_Heap_free(&heap);

    printf("%s %s\n", name, result[0]);
}

void Binomial_Heap_test()
{
    char * name = "[BINOMIAL HEAP TEST]";
    Binomial_Heap_ptr heap = Binomial_Heap_create();
    if (!heap)
    {
        printf("%s %s NO_MEMORY HEAP\n", name, result[1]);
        return;
    }

    Application_ptr application_1 = new_application(time(NULL), 10, "aaaasksks", 1, 12);
    if (!application_1)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_2 = new_application(time(NULL), 9, "aaaasamfksks", 2, 24);
    if (!application_2)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_3 = new_application(time(NULL), 4, "kfW", 6, 2);
    if (!application_3)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    if (Binomial_Heap_insert(&heap, application_1) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }

    if (Binomial_Heap_insert(&heap, application_2) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    if (Binomial_Heap_insert(&heap, application_3) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }

    Application_ptr appl_result = NULL;

    if (Binomial_Heap_get_max(&heap, &appl_result) != success)
    {
        printf("%s %s GET_MAX\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 1 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    appl_result = NULL;
    if (Binomial_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 1\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 2 NOT MAX %d \n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    appl_result = NULL;

    if (Binomial_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 2\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 9)
    {
        printf("%s %s 3 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    Binomial_Heap_free(&heap);

    printf("%s %s\n", name, result[0]);
}

void Fibonacci_Heap_test()
{
    char * name = "[FIBONACCI HEAP TEST]";
    Fibonacci_Heap_ptr heap = Fibonacci_Heap_create();
    if (!heap)
    {
        printf("%s %s NO_MEMORY HEAP\n", name, result[1]);
        return;
    }

    Application_ptr application_1 = new_application(time(NULL), 10, "aaaasksks", 1, 12);
    if (!application_1)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_2 = new_application(time(NULL), 9, "aaaasamfksks", 2, 24);
    if (!application_2)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_3 = new_application(time(NULL), 4, "kfW", 6, 2);
    if (!application_3)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    if (Fibonacci_Heap_insert(&heap, application_1) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }

    if (Fibonacci_Heap_insert(&heap, application_2) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    if (Fibonacci_Heap_insert(&heap, application_3) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }

    Application_ptr appl_result = NULL;

    if (Fibonacci_Heap_get_max(&heap, &appl_result) != success)
    {
        printf("%s %s GET_MAX\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 1 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    appl_result = NULL;
    if (Fibonacci_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 1\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 2 NOT MAX %d \n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    appl_result = NULL;

    if (Fibonacci_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 2\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 9)
    {
        printf("%s %s 3 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    Fibonacci_Heap_free(&heap);

    printf("%s %s\n", name, result[0]);
}

void Leftist_Heap_test()
{
    char * name = "[LEFTIST HEAP TEST]";
    Leftist_Heap_ptr heap = Leftist_Heap_create();
    if (!heap)
    {
        printf("%s %s NO_MEMORY HEAP\n", name, result[1]);
        return;
    }

    Application_ptr application_1 = new_application(time(NULL), 10, "aaaasksks", 1, 12);
    if (!application_1)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_2 = new_application(time(NULL), 9, "aaaasamfksks", 2, 24);
    if (!application_2)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_3 = new_application(time(NULL), 4, "kfW", 6, 2);
    if (!application_3)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    if (Leftist_Heap_insert(&heap, application_1) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }

    if (Leftist_Heap_insert(&heap, application_2) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    if (Leftist_Heap_insert(&heap, application_3) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    Application_ptr appl_result = NULL;

    if (Leftist_Heap_get_max(&heap, &appl_result) != success)
    {
        printf("%s %s GET_MAX\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 1 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    appl_result = NULL;
    if (Leftist_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 1\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 2 NOT MAX %d \n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    appl_result = NULL;

    if (Leftist_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 2\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 9)
    {
        printf("%s %s 3 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    Leftist_Heap_free(&heap);
    printf("%s %s\n", name, result[0]);
}

void Skew_Heap_test()
{
    char * name = "[SKEW HEAP TEST]";
    Skew_Heap_ptr heap = Skew_Heap_create();
    if (!heap)
    {
        printf("%s %s NO_MEMORY HEAP\n", name, result[1]);
        return;
    }

    Application_ptr application_1 = new_application(time(NULL), 10, "aaaasksks", 1, 12);
    if (!application_1)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_2 = new_application(time(NULL), 9, "aaaasamfksks", 2, 24);
    if (!application_2)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_3 = new_application(time(NULL), 4, "kfW", 6, 2);
    if (!application_3)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    if (Skew_Heap_insert(&heap, application_1) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }

    if (Skew_Heap_insert(&heap, application_2) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    if (Skew_Heap_insert(&heap, application_3) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    Application_ptr appl_result = NULL;

    if (Skew_Heap_get_max(&heap, &appl_result) != success)
    {
        printf("%s %s GET_MAX\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 1 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    appl_result = NULL;
    if (Skew_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 1\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 2 NOT MAX %d \n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    appl_result = NULL;

    if (Skew_Heap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 2\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 9)
    {
        printf("%s %s 3 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    Skew_Heap_free(&heap);
    printf("%s %s\n", name, result[0]);
}

void Treap_test()
{
    char * name = "[TREAP TEST]";
    Treap_ptr heap = Treap_create();
    if (!heap)
    {
        printf("%s %s NO_MEMORY HEAP\n", name, result[1]);
        return;
    }

    Application_ptr application_1 = new_application(time(NULL), 10, "aaaasksks", 1, 12);
    if (!application_1)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_2 = new_application(time(NULL), 9, "aaaasamfksks", 2, 24);
    if (!application_2)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    Application_ptr application_3 = new_application(time(NULL), 4, "kfW", 6, 2);
    if (!application_3)
    {
        printf("%s %s NO_MEMORY APPLICATION\n", name, result[1]);
        return;
    }

    if (Treap_insert(&heap, application_1) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }

    if (Treap_insert(&heap, application_2) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    if (Treap_insert(&heap, application_3) != success)
    {
        printf("%s %s INSERT\n", name, result[1]);
        return;
    }
    Application_ptr appl_result = NULL;

    if (Treap_get_max(&heap, &appl_result) != success)
    {
        printf("%s %s GET_MAX\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 1 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    appl_result = NULL;
    if (Treap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 1\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 10)
    {
        printf("%s %s 2 NOT MAX %d \n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    appl_result = NULL;

    if (Treap_delete_max(&heap, &appl_result) != success)
    {
        printf("%s %s DELETE_MAX 2\n", name, result[1]);
        return;
    }
    if (appl_result->priority != 9)
    {
        printf("%s %s 3 NOT MAX %d\n", name, result[1], appl_result->priority);
        return;
    }
    free_application(appl_result);
    Treap_free(&heap);
    printf("%s %s\n", name, result[0]);
}

void run_tests()
{
    Binary_Heap_test();
    Binomial_Heap_test();
    Fibonacci_Heap_test();
    Leftist_Heap_test();
    Treap_test();
}

int main()
{
    run_tests();
    return 0;
}