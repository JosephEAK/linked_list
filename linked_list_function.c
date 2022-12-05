#include "linked_list_function.h"

/*void init_list(node_t **head)
{
    time_t t1;
    srand((unsigned)time(&t1));
    node_t **current = head;
    push_first(current, 5);
    push_first(current, 4);
    push_first(current, 3);
    push_first(current, 2);
    push_first(current, 1);
}*/

node_t *get_new_elem(int num)
{
    node_t *temp = (node_t *)malloc(sizeof(node_t));
    temp->val = num;
    return temp;
}

int print_list(node_t *head)
{
    node_t *current = head;

    if (current == NULL)
        return -1;

    while (current != NULL)
    {
        printf("%d\n", current->val);
        current = current->next;
    }
    return 0;
}

void push_ll(node_t *head, node_t *next_elem)
{
    node_t *first_current = head;

    while (first_current->next != NULL)
    {
        first_current = first_current->next;
    }
    first_current->next = next_elem;
}

int pop_last(node_t *head)
{
    int retval = 0; // retrieve value
    if (head->next == NULL)
    {
        retval = head->val;
        free(head);
        return retval;
    }

    node_t *current = head;
    while (current->next->next != NULL) // tant que la valeur de la prochaine prochaine valeur n'est pas NULL on itère. Puisque que l'on veut la derniere de la liste.
    {
        current = current->next;
    }

    retval = current->next->val;
    free(current->next);  // on supprime de la memoire
    current->next = NULL; // on y met NULL
    return retval;
}

int length_list(node_t *head)
{
    int count = 1;

    if (head == NULL)
        return 0;

    if (head->next == NULL)
        return 1;

    node_t *current = head;

    while (current->next != NULL)
    {
        count += 1;
        current = current->next;
    }
    return count;
}

int push_index_ll(node_t *head, node_t *next_elem, int index)
{

    int i;
    node_t *current = head;
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    if (index == 0)
    {
        // push_first(head, val);
        return -1;
    }

    for (i = 0; i < index - 1; i++)
    {
        if (current->next == NULL)
            return -1;

        current = current->next;
    }
    new_node->val = next_elem->val;
    new_node->next = current->next;
    current->next = new_node;
    return 0;
}

int pop_index(node_t *head, int index)
{
    int i;
    int retval = -1;
    node_t *current = head;
    node_t *temp_node = NULL;

    if (index == 0)
    {
        // return pop_first(head);
    }

    for (i = 0; i < index - 1; i++)
    {
        if (current->next == NULL)
            return -1;

        current = current->next;
    }

    temp_node = current->next;
    current->next = temp_node->next;
    retval = temp_node->val;
    free(temp_node);

    return retval;
}

int swap_(node_t **head, int index1, int index2)
{
    node_t *current = *head;
    int temp1 = 0, temp2 = 0, i = 0;

    if (index2 < index1)
    {
        temp1 = index1;
        index1 = index2;
        index2 = temp1;
    }

    if (index1 == 0)
        temp1 = **(int **)head;

    for (i = 0; i < index2 - 1; i++)
    {
        if (current->next == NULL)
            return -1;

        if (i == index1 - 1 && index1 > 0)
            temp1 = current->next->val;

        current = current->next;
    }
    temp2 = current->next->val;

    current = *head;

    if (index1 == 0)
        current->val = temp2;

    for (i = 0; i < index2 - 1; i++)
    {
        if (i == index1 - 1 && index1 > 0)
            *(int *)current->next = temp2;

        current = current->next;
    }

    *(int *)current->next = temp1;
    return 0;
}

int search(node_t **head, int key)
{
    node_t *current = *head;
    while (current != NULL)
    {
        if (current->val == key)
            return 1;
        current = current->next;
    }
    return -1;
}

void free_list(node_t *head)
{
    node_t *current;

    while (head != NULL)
    {
        current = head;
        head = head->next;
        free(current);
    }
}

/*
void push_last(node_t *head, int val)
{
    node_t *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = (node_t *)malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

void push_first(node_t **head, int val)
{
    node_t *new_node;
    new_node = (node_t *)malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

int pop_first(node_t **head)
{
    int retval = -1;
    node_t *next_node = NULL;

    if (*head == NULL)
        return -1;

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    (*head) = next_node;

    return retval;
}

int push_index(node_t **head, int index, int val) // besoin d'un pointer de pointer, va pointer sur la liste
{
    int i;
    node_t *current = *head;
    node_t *new_node = (node_t *)malloc(sizeof(node_t));

    if (index == 0)
    {
        push_first(head, val);
        return -1;
    }

    for (i = 0; i < index - 1; i++)
    {
        if (current->next == NULL)
            return -1;

        current = current->next;
    }
    new_node->val = val;
    new_node->next = current->next;
    current->next = new_node;
}

*/