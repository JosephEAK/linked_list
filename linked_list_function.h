#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER

typedef struct linked_list
{
    int data;
    struct linked_list *next;
} linked_list;

linked_list *ll_get_new_elem(int data);
void ll_push_elem(linked_list *list, linked_list *elem);
void ll_pop(linked_list *list);
void ll_free(linked_list *list);
int ll_length(linked_list *list);
void ll_add_index(linked_list **list, int index, linked_list *elem);
void ll_print(linked_list *list);
linked_list *ll_elem_at_index(linked_list *list, int index);
void ll_swap_index(linked_list **list, int index0, int index1);
void ll_reverse(linked_list **list);
void ll_remove_data_sup(linked_list **list, int value);

typedef struct double_linked_list
{
    int data;
    struct double_linked_list *prev;
    struct double_linked_list *next;
} double_linked_list;

double_linked_list *d_ll_get_new_elem(int data);
void d_ll_push_elem(double_linked_list *list, double_linked_list *elem);
void d_ll_pop(double_linked_list *list);
void d_ll_free(double_linked_list *list);
void d_ll_print(double_linked_list *list);
int d_ll_length(double_linked_list *list);
void d_ll_add_index(double_linked_list **list, int index, double_linked_list *elem);

#endif