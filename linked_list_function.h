#ifndef LIST_HEADER
#define LIST_HEADER

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
    int val;
    struct node_t *next;
} node_t;

void init_list(node_t **head);
int print_list(node_t *head);
int pop_last(node_t *head);
void push_last(node_t *head, int val);
int pop_first(node_t **head);
void push_first(node_t **head, int val);
int push_index(node_t **head, int index, int val);
int pop_index(node_t *head, int index);
int length_list(node_t *head);
int search(node_t **head, int key);
node_t *get_new_elem(int num);
void push_ll(node_t *head, node_t *next_elem);
int push_index_ll(node_t *head, node_t *next_elem, int index);
int swap_(node_t **head, int index1, int index2);
void free_list(node_t *head);

#endif