#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

double_linked_list* d_ll_get_new_elem(int data){
	double_linked_list* new_elem = (double_linked_list*) malloc(sizeof(double_linked_list));

	new_elem->data = data;
	new_elem->next = NULL;
	new_elem->prev = NULL;

	return new_elem;
}

void d_ll_push_elem(double_linked_list* list, double_linked_list* elem){
	double_linked_list* pt = list;

	while(pt->next != NULL){
		pt = pt->next;
	}

	pt->next = elem;
	elem->prev = pt;

}


void d_ll_pop(double_linked_list* list){
	double_linked_list* pt = list;

	if(pt->next == NULL){
		return;
	}

	while(pt->next != NULL){
		pt = pt->next;
	}

	pt->prev->next = NULL;
	free(pt);
}


void d_ll_free(double_linked_list* list){
	double_linked_list* pt = list;
	double_linked_list* pt_prev;

	while (pt != NULL){
		pt_prev = pt;
		pt = pt->next;
		free(pt_prev);
	}

}


void d_ll_print(double_linked_list* list){
	double_linked_list* pt;
	pt = list;

	while (pt != NULL){
		printf("[%d]<->",pt->data);
		pt = pt->next;
	}
	printf("\n");
}


int d_ll_length(double_linked_list* list){
	double_linked_list* pt = list;
	int len = 0;

	while (pt != NULL){
		pt = pt->next;
		len++;
	}

	return len;
}


void d_ll_add_index(double_linked_list** list,int index,double_linked_list* elem){
	double_linked_list* pt = *list;
	double_linked_list* tmp;
	int id = 0;
	int len;

	if(index == 0){ // in case we want to replace the first elem
		elem->next = *list;
		elem->prev = NULL;
		*list = elem;
		return;
	}

	len = d_ll_length(*list);

	if (index >= len){
		d_ll_push_elem(*list,elem);
		return;
	}

	while (pt != NULL && id != index - 1 && id < len-1){
		pt = pt->next;
		id++;
	}

	tmp = pt->next;
	tmp->prev = elem;
	pt->next = elem;
	elem->next = tmp;
	elem->prev = pt;

	/*pt elem tmp*/
}
