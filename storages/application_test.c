#include "application_storage.h"

int main()
{
    Application_storage_ptr storage = application_storage_create(BinaryHeap_T);
    if (!storage)
    {
        printf("NO_MEMORY\n");
        return no_memory;
    }

    Application_ptr application_1 = new_application(time(NULL), 4, "aaaksks", 7, 123);
    if (!application_1)
    {
        printf("NO_MEMORY\n");
        return no_memory;
    }

    Application_ptr application_2 = new_application(time(NULL), 9, "aaaR Jasksks", 3, 1241);
    if (!application_1)
    {
        printf("NO_MEMORY\n");
        return no_memory;
    }

    Application_ptr application_3 = new_application(time(NULL), 18, "Jsksks", 10, 1287529);
    if (!application_1)
    {
        printf("NO_MEMORY\n");
        return no_memory;
    }

    Application_ptr application_4 = new_application(time(NULL), 1, "aTIHGs", 4, 123);
    if (!application_1)
    {
        printf("NO_MEMORY\n");
        return no_memory;
    }

    status error;
    if ((error = storage->insert(&storage->storage, application_1)) != success)
    {
        printf("SOME ERROR INSERT\n");
        return error;
    }

    if ((error = storage->insert(&storage->storage, application_2)) != success)
    {
        printf("SOME ERROR INSERT\n");
        return error;
    }

    if ((error = storage->insert(&storage->storage, application_3)) != success)
    {
        printf("SOME ERROR INSERT\n");
        return error;
    }

    if ((error = storage->insert(&storage->storage, application_4)) != success)
    {
        printf("SOME ERROR INSERT\n");
        return error;
    }

    Application_ptr appl = NULL;
    if ((error = storage->delete_max(&storage->storage, &appl)) != success)
    {
        printf("SOME ERROR DELETE MAX\n");
        return error;
    }
    if (appl->priority != 18)
    {
        printf("NOT MAX\n");
        return -1;
    }
    free_application(appl);
    appl = NULL;

    if ((error = storage->delete_max(&storage->storage, &appl)) != success)
    {
        printf("SOME ERROR DELETE MAX\n");
        return error;
    }
    if (appl->priority != 9)
    {
        printf("NOT MAX\n");
        return -1;
    }
    free_application(appl);
    appl = NULL;

    if ((error = storage->delete_max(&storage->storage, &appl)) != success)
    {
        printf("SOME ERROR DELETE MAX\n");
        return error;
    }
    if (appl->priority != 4)
    {
        printf("NOT MAX\n");
        return -1;
    }
    free_application(appl);

    storage->free(&storage->storage);
    free(storage);
    printf("\n[TEST PASSED]\n\n");
    return success;
}