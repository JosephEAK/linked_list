#include <string.h>
#include <sys/stat.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "linked_list_function.h"

void test_ll_get_new_elem()
{

    linked_list *elem = ll_get_new_elem(12);

    CU_ASSERT(elem->data == 12);
    CU_ASSERT(elem->next == NULL);

    free(elem);
}

void test_ll_push_elem()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *pt = HEAD;

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);

    CU_ASSERT(pt->data == 11);
    CU_ASSERT(pt->next == elem0);
    pt = pt->next;
    CU_ASSERT(pt->data == 12);
    CU_ASSERT(pt->next == elem1);
    pt = pt->next;
    CU_ASSERT(pt->data == 13);
    CU_ASSERT(pt->next == NULL);

    free(elem0);
    free(elem1);
    free(HEAD);
}

void test_ll_pop()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);

    ll_pop(HEAD);

    CU_ASSERT(elem0->next == NULL);
    CU_ASSERT(HEAD->next == elem0);

    free(elem0);
    free(HEAD);
}

void test_ll_pop_empty()
{

    linked_list *HEAD = ll_get_new_elem(11);

    ll_pop(HEAD);

    CU_ASSERT(HEAD->next == NULL);

    free(HEAD);
}

void test_ll_free()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);

    ll_free(HEAD); // Usefull only with valgrind
}

void test_ll_length()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);

    CU_ASSERT(ll_length(HEAD) == 3);
    CU_ASSERT(ll_length(elem0) == 2);
    CU_ASSERT(ll_length(elem1) == 1);

    ll_free(HEAD);
}

void test_ll_add_index()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem_add = ll_get_new_elem(100);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);

    /*ll_print(HEAD);*/
    ll_add_index(&HEAD, 1, elem_add);
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_length(HEAD) == 4);
    CU_ASSERT(HEAD->next == elem_add);
    CU_ASSERT(elem_add->next == elem0);

    ll_free(HEAD);
}

void test_ll_add_index_too_big()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem_add = ll_get_new_elem(100);
    linked_list *pt = HEAD;

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);

    /*ll_print(HEAD);*/
    ll_add_index(&HEAD, 5, elem_add);
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_length(HEAD) == 4);

    CU_ASSERT(pt->data == 11);
    CU_ASSERT(pt->next == elem0);
    pt = pt->next;
    CU_ASSERT(pt->data == 12);
    CU_ASSERT(pt->next == elem1);
    pt = pt->next;
    CU_ASSERT(pt->data == 13);
    CU_ASSERT(pt->next == elem_add);
    pt = pt->next;
    CU_ASSERT(pt->data == 100);
    CU_ASSERT(pt->next == NULL);

    ll_free(HEAD);
}

void test_ll_add_index_first()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem_add = ll_get_new_elem(100);
    linked_list *pt;

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);

    /*ll_print(HEAD);*/
    ll_add_index(&HEAD, 0, elem_add);
    /*ll_print(HEAD);*/

    pt = HEAD;
    CU_ASSERT(ll_length(HEAD) == 4);

    CU_ASSERT(pt->data == 100);
    pt = pt->next;
    CU_ASSERT(pt->data == 11);
    CU_ASSERT(pt->next == elem0);
    pt = pt->next;
    CU_ASSERT(pt->data == 12);
    CU_ASSERT(pt->next == elem1);
    pt = pt->next;
    CU_ASSERT(pt->data == 13);
    CU_ASSERT(pt->next == NULL);

    ll_free(HEAD);
}

void test_ll_elem_at_index()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == HEAD);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem1);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem1);

    ll_free(HEAD);
}

void test_ll_swap_index_general()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(15);
    linked_list *elem4 = ll_get_new_elem(16);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_swap_index(&HEAD, 2, 4); // Genral case
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == HEAD);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem3);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem2);
    CU_ASSERT(ll_elem_at_index(HEAD, 4) == elem1);
    CU_ASSERT(ll_elem_at_index(HEAD, 5) == elem4);

    ll_free(HEAD);
}

void test_ll_swap_index_general_edge()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(15);
    linked_list *elem4 = ll_get_new_elem(16);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_swap_index(&HEAD, 3, 5); // Genral case
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == HEAD);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem1);
    CU_ASSERT(ll_elem_at_index(HEAD, 5) == elem2);
    CU_ASSERT(ll_elem_at_index(HEAD, 4) == elem3);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem4);

    ll_free(HEAD);
}

void test_ll_swap_index_glued()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(15);
    linked_list *elem4 = ll_get_new_elem(16);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_swap_index(&HEAD, 3, 4); // Genral case
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == HEAD);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem1);
    CU_ASSERT(ll_elem_at_index(HEAD, 4) == elem2);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem3);
    CU_ASSERT(ll_elem_at_index(HEAD, 5) == elem4);

    ll_free(HEAD);
}

void test_ll_swap_index_glued_edge()
{

    linked_list *HEAD = ll_get_new_elem(11);
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(15);
    linked_list *elem4 = ll_get_new_elem(16);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_swap_index(&HEAD, 4, 5); // Genral case
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == HEAD);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem1);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem2);
    CU_ASSERT(ll_elem_at_index(HEAD, 5) == elem3);
    CU_ASSERT(ll_elem_at_index(HEAD, 4) == elem4);

    ll_free(HEAD);
}

void test_ll_swap_index_head()
{

    linked_list *elem_HEAD = ll_get_new_elem(11);
    linked_list *HEAD = elem_HEAD;
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(15);
    linked_list *elem4 = ll_get_new_elem(16);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_swap_index(&HEAD, 0, 4); // Genral case
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == elem3);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem1);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem2);
    CU_ASSERT(ll_elem_at_index(HEAD, 4) == elem_HEAD);
    CU_ASSERT(ll_elem_at_index(HEAD, 5) == elem4);

    ll_free(HEAD);
}

void test_ll_swap_index_head_headp1()
{

    linked_list *elem_HEAD = ll_get_new_elem(11);
    linked_list *HEAD = elem_HEAD;
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(15);
    linked_list *elem4 = ll_get_new_elem(16);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_swap_index(&HEAD, 0, 1); // Genral case
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem_HEAD);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem1);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem2);
    CU_ASSERT(ll_elem_at_index(HEAD, 4) == elem3);
    CU_ASSERT(ll_elem_at_index(HEAD, 5) == elem4);

    ll_free(HEAD);
}

void test_ll_reverse()
{

    linked_list *elem_HEAD = ll_get_new_elem(11);
    linked_list *HEAD = elem_HEAD;
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(13);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(15);
    linked_list *elem4 = ll_get_new_elem(16);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_reverse(&HEAD);
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == elem4);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem3);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem2);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem1);
    CU_ASSERT(ll_elem_at_index(HEAD, 4) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 5) == elem_HEAD);

    ll_free(HEAD);
}

void test_ll_remove_data_sup()
{

    linked_list *elem_HEAD = ll_get_new_elem(11);
    linked_list *HEAD = elem_HEAD;
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(15);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(16);
    linked_list *elem4 = ll_get_new_elem(11);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_remove_data_sup(&HEAD, 14);
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == elem_HEAD);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 2) == elem2);
    CU_ASSERT(ll_elem_at_index(HEAD, 3) == elem4);

    ll_free(HEAD);
}

void test_ll_remove_data_sup_edge()
{

    linked_list *elem_HEAD = ll_get_new_elem(16);
    linked_list *HEAD = elem_HEAD;
    linked_list *elem0 = ll_get_new_elem(12);
    linked_list *elem1 = ll_get_new_elem(15);
    linked_list *elem2 = ll_get_new_elem(14);
    linked_list *elem3 = ll_get_new_elem(16);
    linked_list *elem4 = ll_get_new_elem(18);

    ll_push_elem(HEAD, elem0);
    ll_push_elem(HEAD, elem1);
    ll_push_elem(HEAD, elem2);
    ll_push_elem(HEAD, elem3);
    ll_push_elem(HEAD, elem4);

    /*ll_print(HEAD);*/
    ll_remove_data_sup(&HEAD, 14);
    /*ll_print(HEAD);*/

    CU_ASSERT(ll_elem_at_index(HEAD, 0) == elem0);
    CU_ASSERT(ll_elem_at_index(HEAD, 1) == elem2);

    ll_free(HEAD);
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
        NULL == CU_add_test(pSuite, "test_ll_get_new_elem()", test_ll_get_new_elem) ||
        NULL == CU_add_test(pSuite, "test_ll_push_elem()", test_ll_push_elem) ||
        NULL == CU_add_test(pSuite, "test_ll_pop()", test_ll_pop) ||
        NULL == CU_add_test(pSuite, "test_ll_pop_empty()", test_ll_pop_empty) ||
        NULL == CU_add_test(pSuite, "test_ll_free()", test_ll_free) ||
        NULL == CU_add_test(pSuite, "test_ll_length()", test_ll_length) ||
        NULL == CU_add_test(pSuite, "test_ll_add_index()", test_ll_add_index) ||
        NULL == CU_add_test(pSuite, "test_ll_add_index_too_big()", test_ll_add_index_too_big) ||
        NULL == CU_add_test(pSuite, "test_ll_add_index_first()", test_ll_add_index_first) ||
        NULL == CU_add_test(pSuite, "test_ll_elem_at_index()", test_ll_elem_at_index) ||
        NULL == CU_add_test(pSuite, "test_ll_swap_index_general()", test_ll_swap_index_general) ||
        NULL == CU_add_test(pSuite, "test_ll_swap_index_glued()", test_ll_swap_index_glued) ||
        NULL == CU_add_test(pSuite, "test_ll_swap_index_general_edge()", test_ll_swap_index_general_edge) ||
        NULL == CU_add_test(pSuite, "test_ll_swap_index_glued_edge()", test_ll_swap_index_glued_edge) ||
        NULL == CU_add_test(pSuite, "test_ll_swap_index_head()", test_ll_swap_index_head) ||
        NULL == CU_add_test(pSuite, "test_ll_swap_index_head_headp1()", test_ll_swap_index_head_headp1) ||
        NULL == CU_add_test(pSuite, "test_ll_reverse()", test_ll_reverse) ||
        NULL == CU_add_test(pSuite, "test_ll_remove_data_sup()", test_ll_remove_data_sup) ||
        NULL == CU_add_test(pSuite, "test_ll_remove_data_sup_edge()", test_ll_remove_data_sup_edge))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}