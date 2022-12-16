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