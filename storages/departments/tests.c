#include "department.h"
#include "../../application.h"
#include "../application_storage.h"
#include "BinarySearchTree.h"
#include "DynamicArray.h"
#include "HashSet.h"
#include "Trie.h"

void BST_test()
{
    BST_ptr tree = BST_create();
    
    Application_storage_ptr storage_1 = application_storage_create(BinaryHeap_T);
    Department_ptr dep_1 = department_create(123, storage_1, 2, 1.2);

    Application_storage_ptr storage_2 = application_storage_create(LeftistHeap_T);
    Department_ptr dep_2 = department_create(1233, storage_2, 10, 1.5);

    Application_storage_ptr storage_3 = application_storage_create(SkewHeap_T);
    Department_ptr dep_3 = department_create(1232, storage_3, 20, 1.3);

    Application_storage_ptr storage_4 = application_storage_create(BinomialHeap_T);
    Department_ptr dep_4 = department_create(12143, storage_4, 8, 1.2);
    
    Application_storage_ptr storage_5 = application_storage_create(Treap_T);
    Department_ptr dep_5 = department_create(12183, storage_5, 5, 1.9);

    status st;
    st = BST_insert(tree, 123, dep_1);
    if (st != success) printf("[BST] insertion failed\n");
    
    st = BST_insert(tree, 1233, dep_2);
    if (st != success) printf("[BST] insertion failed\n");
    st = BST_insert(tree, 1232, dep_3);
    if (st != success) printf("[BST] insertion failed\n");
    st = BST_insert(tree, 12143, dep_4);
    if (st != success) printf("[BST] insertion failed\n");
    st = BST_insert(tree, 12183, dep_5);
    if (st != success) printf("[BST] insertion failed\n");

    Department_ptr dep = NULL;
    st = BST_find(tree, 1232, &dep);
    if (st != success) printf("[BST] find failed\n");
    if (dep->free_operators->size != 20) printf("[BST] wrong operators count\n");
    if (dep->identifier != 1232) printf("[BST] wrong identifier\n");

    BST_free(tree);

    printf("[BST] PASSED\n");
}

void Dynamic_Array_test()
{
    Dynamic_Array_ptr tree = dynamic_array_create();
    
    Application_storage_ptr storage_1 = application_storage_create(BinaryHeap_T);
    Department_ptr dep_1 = department_create(123, storage_1, 2, 1.2);

    Application_storage_ptr storage_2 = application_storage_create(LeftistHeap_T);
    Department_ptr dep_2 = department_create(1233, storage_2, 10, 1.5);

    Application_storage_ptr storage_3 = application_storage_create(SkewHeap_T);
    Department_ptr dep_3 = department_create(1232, storage_3, 20, 1.3);

    Application_storage_ptr storage_4 = application_storage_create(BinomialHeap_T);
    Department_ptr dep_4 = department_create(12143, storage_4, 8, 1.2);
    
    Application_storage_ptr storage_5 = application_storage_create(Treap_T);
    Department_ptr dep_5 = department_create(12183, storage_5, 5, 1.9);

    status st;
    st = dynamic_array_insert(tree, 123, dep_1);
    if (st != success) printf("[DYNAMIC ARRAY] insertion failed\n");
    
    st = dynamic_array_insert(tree, 1233, dep_2);
    if (st != success) printf("[DYNAMIC ARRAY] insertion failed\n");
    st = dynamic_array_insert(tree, 1232, dep_3);
    if (st != success) printf("[DYNAMIC ARRAY] insertion failed\n");
    st = dynamic_array_insert(tree, 12143, dep_4);
    if (st != success) printf("[DYNAMIC ARRAY] insertion failed\n");
    st = dynamic_array_insert(tree, 12183, dep_5);
    if (st != success) printf("[DYNAMIC ARRAY] insertion failed\n");

    Department_ptr dep = NULL;
    st = dynamic_array_find(tree, 12143, &dep);
    
    if (st != success) printf("[DYNAMIC ARRAY] find failed\n");
    if (dep->free_operators->size != 8) printf("[DYNAMIC ARRAY] wrong operators count\n");
    if (dep->identifier != 12143) printf("[DYNAMIC ARRAY] wrong identifier\n");

    dynamic_array_free(tree);

    printf("[DYNAMIC ARRAY] PASSED\n");
}

void Hash_Set_test()
{
    Hash_Set_ptr tree = HS_create();
    
    Application_storage_ptr storage_1 = application_storage_create(BinaryHeap_T);
    Department_ptr dep_1 = department_create(123, storage_1, 2, 1.2);

    Application_storage_ptr storage_2 = application_storage_create(LeftistHeap_T);
    Department_ptr dep_2 = department_create(1233, storage_2, 10, 1.5);

    Application_storage_ptr storage_3 = application_storage_create(SkewHeap_T);
    Department_ptr dep_3 = department_create(1232, storage_3, 20, 1.3);

    Application_storage_ptr storage_4 = application_storage_create(BinomialHeap_T);
    Department_ptr dep_4 = department_create(12143, storage_4, 8, 1.2);
    
    Application_storage_ptr storage_5 = application_storage_create(Treap_T);
    Department_ptr dep_5 = department_create(12183, storage_5, 5, 1.9);

    status st;
    st = HS_insert(tree, 123, dep_1);
    if (st != success) printf("[HASH SET] insertion failed\n");
    
    st = HS_insert(tree, 1233, dep_2);
    if (st != success) printf("[HASH SET] insertion failed\n");
    st = HS_insert(tree, 1232, dep_3);
    if (st != success) printf("[HASH SET] insertion failed\n");
    st = HS_insert(tree, 12143, dep_4);
    if (st != success) printf("[HASH SET] insertion failed\n");
    st = HS_insert(tree, 12183, dep_5);
    if (st != success) printf("[HASH SET] insertion failed\n");

    Department_ptr dep = NULL;
    st = HS_find(tree, 12143, &dep);
    
    if (st != success) printf("[HASH SET] find failed\n");
    if (dep->free_operators->size != 8) printf("[HASH SET] wrong operators count\n");
    if (dep->identifier != 12143) printf("[HASH SET] wrong identifier\n");

    HS_free(tree);

    printf("[HASH SET] PASSED\n");
}

void Trie_test()
{
    Trie_ptr tree = Trie_create();
    
    Application_storage_ptr storage_1 = application_storage_create(BinaryHeap_T);
    Department_ptr dep_1 = department_create(123, storage_1, 2, 1.2);

    Application_storage_ptr storage_2 = application_storage_create(LeftistHeap_T);
    Department_ptr dep_2 = department_create(1233, storage_2, 10, 1.5);

    Application_storage_ptr storage_3 = application_storage_create(SkewHeap_T);
    Department_ptr dep_3 = department_create(1232, storage_3, 20, 1.3);

    Application_storage_ptr storage_4 = application_storage_create(BinomialHeap_T);
    Department_ptr dep_4 = department_create(12143, storage_4, 8, 1.2);
    
    Application_storage_ptr storage_5 = application_storage_create(Treap_T);
    Department_ptr dep_5 = department_create(12183, storage_5, 5, 1.9);

    status st;
    st = Trie_insert(tree, 123, dep_1);
    if (st != success) printf("[TRIE] insertion failed\n");
    
    st = Trie_insert(tree, 1233, dep_2);
    if (st != success) printf("[TRIE] insertion failed\n");
    st = Trie_insert(tree, 1232, dep_3);
    if (st != success) printf("[TRIE] insertion failed\n");
    st = Trie_insert(tree, 12143, dep_4);
    if (st != success) printf("[TRIE] insertion failed\n");
    st = Trie_insert(tree, 12183, dep_5);
    if (st != success) printf("[TRIE] insertion failed\n");

    Department_ptr dep = NULL;
    st = Trie_find(tree, 1232, &dep);
    if (st != success) printf("[TRIE] find failed\n");
    if (dep->free_operators->size != 20) printf("[BST] wrong operators count\n");
    if (dep->identifier != 1232) printf("[TRIE] wrong identifier\n");

    Trie_free(tree);

    printf("[TRIE] PASSED\n");
}

void run_tests()
{
    BST_test();
    Dynamic_Array_test();
    Hash_Set_test();
    Trie_test();
}

int main()
{
    run_tests();
    return 0;
}