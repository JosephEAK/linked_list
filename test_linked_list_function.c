#include <string.h>
#include <sys/stat.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "linked_list_function.h"
/*
void test_push_pop(void)
{
    int free_val;
    node_t *test_list = (node_t *)malloc(sizeof(node_t));
    test_list->val = 1;

    node_t **ptr_test_list = (node_t **)malloc(sizeof(node_t *));
    ptr_test_list = &test_list;

    init_list(ptr_test_list);

    push_last(test_list, 10);
    CU_ASSERT(test_list->next->next->next->next->val == 10);

    free_val = pop_last(test_list);
    CU_ASSERT(free_val == 10);

    push_index(ptr_test_list, 1, 5); // ptr sur la liste, l'index en commençant par 0, le chiffre a ajouter
    CU_ASSERT(test_list->next->val == 5);

    push_index(ptr_test_list, 2, 8); // ptr sur la liste, l'index en commençant par 0, le chiffre a ajouter
    CU_ASSERT(test_list->next->next->val == 8);

    push_first(ptr_test_list, 9);
    CU_ASSERT(test_list->val == 9);

    push_index(ptr_test_list, 0, 11);
    CU_ASSERT(test_list->val == 11);
    // print_list(test_list);
    // printf("\n");

    free_val = pop_index(ptr_test_list, 4);
    CU_ASSERT(free_val == 8);

    free_val = pop_first(ptr_test_list);
    CU_ASSERT(free_val == 11);

    // print_list(test_list);
}
*/
void test_push(void)
{
    node_t *HEAD = get_new_elem(10);
    node_t *elem1 = get_new_elem(5);
    node_t *elem2 = get_new_elem(7);
    node_t *elem3 = get_new_elem(72);
    node_t *ptr = HEAD;

    push_ll(HEAD, elem1);
    push_ll(elem1, elem2);
    push_ll(elem2, elem3);

    CU_ASSERT(HEAD->val == 10);
    CU_ASSERT(ptr->next->val == 5);
    CU_ASSERT(ptr->next->next->val == 7);
    CU_ASSERT(ptr->next->next->next->val == 72);

    node_t *elem4 = get_new_elem(9);
    node_t *elem5 = get_new_elem(119);
    push_index_ll(HEAD, elem4, 2);
    push_index_ll(HEAD, elem5, 3);
    CU_ASSERT(ptr->next->next->val == 9);
    CU_ASSERT(ptr->next->next->next->val == 119);
    CU_ASSERT(ptr->next->next->next->next->val == 7);
    CU_ASSERT(ptr->next->next->next->next->next->val == 72);

    node_t *pre_HEAD_1 = get_new_elem(78);
    ptr = pre_HEAD_1;

    push_ll(pre_HEAD_1, HEAD);
    CU_ASSERT(ptr->val == 78);
    CU_ASSERT(ptr->next->val == 10);
    CU_ASSERT(ptr->next->next->val == 5);

    free_list(pre_HEAD_1);
}

void test_pop(void)
{
    int free_val;
    node_t *HEAD = get_new_elem(10);
    node_t *elem1 = get_new_elem(5);
    node_t *elem2 = get_new_elem(7);
    node_t *elem3 = get_new_elem(72);
    node_t *elem4 = get_new_elem(8);
    node_t *ptr = HEAD;

    push_ll(HEAD, elem1);
    push_ll(elem1, elem2);
    push_ll(elem2, elem3);
    push_ll(elem3, elem4);

    free_val = pop_last(HEAD);
    CU_ASSERT(free_val == 8);

    free_val = pop_index(HEAD, 1);
    CU_ASSERT(free_val == 5);
    CU_ASSERT(ptr->next->val == 7);

    free_list(HEAD);
}

void test_length_list(void)
{

    node_t *HEAD = get_new_elem(10);
    node_t *elem1 = get_new_elem(5);
    node_t *elem2 = get_new_elem(7);
    node_t *elem3 = get_new_elem(72);

    push_ll(HEAD, elem1);
    push_ll(elem1, elem2);
    push_ll(elem2, elem3);

    CU_ASSERT(length_list(HEAD) == 4);
    CU_ASSERT(length_list(elem2) == 2);
    free_list(HEAD);
}

void test_swap_()
{
    node_t *HEAD = get_new_elem(10);
    node_t *elem1 = get_new_elem(5);
    node_t *elem2 = get_new_elem(7);
    node_t *elem3 = get_new_elem(72);

    node_t **ptr_HEAD = (node_t **)malloc(sizeof(node_t *));
    ptr_HEAD = &HEAD;

    push_ll(HEAD, elem1);
    push_ll(elem1, elem2);
    push_ll(elem2, elem3);

    swap_(ptr_HEAD, 1, 3);
    CU_ASSERT(HEAD->next->val == 72);

    swap_(ptr_HEAD, 0, 1);
    CU_ASSERT(HEAD->val == 72);

    free_list(HEAD);
}

void test_search(void)
{
    node_t *HEAD = get_new_elem(10);
    node_t *elem1 = get_new_elem(5);
    node_t *elem2 = get_new_elem(7);
    node_t *elem3 = get_new_elem(72);

    node_t **ptr_HEAD = (node_t **)malloc(sizeof(node_t *));
    ptr_HEAD = &HEAD;

    push_ll(HEAD, elem1);
    push_ll(elem1, elem2);
    push_ll(elem2, elem3);

    CU_ASSERT(search(ptr_HEAD, 72) == 1);
    CU_ASSERT(search(ptr_HEAD, 11) == -1);
    free_list(HEAD);
}

void test_free_list(void)
{
    node_t *HEAD = get_new_elem(10);
    node_t *elem1 = get_new_elem(5);
    node_t *elem2 = get_new_elem(7);
    node_t *elem3 = get_new_elem(72);

    push_ll(HEAD, elem1);
    push_ll(elem1, elem2);
    push_ll(elem2, elem3);

    free_list(HEAD);
}

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if (
        NULL == CU_add_test(pSuite, "test of test_pop()", test_pop) ||
        NULL == CU_add_test(pSuite, "test of test_push()", test_push) ||
        NULL == CU_add_test(pSuite, "test of test_length_list()", test_length_list) ||
        NULL == CU_add_test(pSuite, "test of test_swap_()", test_swap_) ||
        NULL == CU_add_test(pSuite, "test of test_search()", test_search) ||
        NULL == CU_add_test(pSuite, "test of test_free_list()", test_free_list)
        /**/
    )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}