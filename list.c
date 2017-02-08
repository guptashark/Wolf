#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "custom_mem.h"

struct list_node {
	void *item;
	struct list_node *next;
};

static
int 
list_node_init(
	struct list_node **ln_ptr, 
	void *item)
{
	if(NULL == ln_ptr) return 1;
	if(NULL != *ln_ptr) return 2;

	struct list_node *ret = NULL;
	ret = custom_malloc(sizeof(struct list_node));

	if(NULL == ret) return 3;

	ret->item = item;
	ret->next = NULL;
	*ln_ptr = ret;
	return 0;
}

struct list {
	int length;
	struct list_node *front;
	struct list_node *back;

	int (*item_cmp)(void *, void *, int *);
	int (*item_print)(void *);
};

int list_init(
	struct list **lst_ptr, 
	int (*item_cmp)(void *, void *, int *),
	int (*item_print)(void *))
{
	if(NULL == lst_ptr) return 1;
	if(NULL != *lst_ptr) return 2;
	
	struct list *ret = custom_malloc(sizeof(struct list));
	
	if(NULL == ret) return 3;

	ret->front = NULL;
	ret->back = NULL;
	ret->length = 0;

	ret->item_cmp = item_cmp;
	ret->item_print = item_print;

	*lst_ptr = ret;
				
	return 0;

}

int list_push_front(struct list *lst, void *item) {
	if(NULL == lst) return 1;
	if(NULL == item) return 2;

	struct list_node *to_add = NULL;
	list_node_init(&to_add, item);
	
	if(0 == lst->length) {
		lst->front = to_add;
		lst->back = to_add;
	} else {
		to_add->next = lst->front;
		lst->front = to_add;
	}

	lst->length++;
	return 0;
}

int list_pop_front(struct list *lst, void **item_ptr) {
	if(NULL == lst) return 1;
	if(NULL == item_ptr) return 2;
	if(NULL != *item_ptr) return 3;
	if(0 == lst->length) return 4;

	struct list_node *to_pop = lst->front;
	*item_ptr = to_pop->item;
	lst->front = to_pop->next;
	to_pop->next = NULL;
	custom_free(to_pop);
	lst->length--;
	return 0;
}
	

int list_push_back(struct list *lst, void *item) {
	if(NULL == lst) return 1;
	if(NULL == item) return 2;

	struct list_node *to_add = NULL;
	list_node_init(&to_add, item);

	if(0 == lst->length) {
		lst->front = to_add;
		lst->back = to_add;
	} else {
		lst->back->next = to_add;
		lst->back = to_add;
	}

	lst->length++;
	return 0;
}

int list_length(struct list *lst, int *len_ptr) {
	if(NULL == lst) return 1;
	if(NULL == len_ptr) return 2;
	*len_ptr = lst->length;
	return 0;
}

int list_contains(struct list *lst, void *item, bool *result) {
	if(NULL == lst) return 1;
	if(NULL == item) return 2;
	if(NULL == result) return 3;

	if(lst->length == 0) {
		*result = false;
		return 0;
	}

	struct list_node *current = lst->front;
	int cmp_ret = 0;
	while(current != NULL) {
		lst->item_cmp(item, current->item, &cmp_ret);
		if(0 == cmp_ret) {
			*result = true;
			return 0;
		}
	}

	*result = false;
	return 0;
}


int list_access(struct list *lst, int index, void **item_ptr) {
	if(NULL == lst) return 1;
	if(index < 0) return 2;
	if(index >= lst->length) return 3;
	if(NULL == item_ptr) return 4;
	if(NULL != *item_ptr) return 5;

	struct list_node *current = lst->front;
	for(int i = 0; i < index; i++) {
		current = current->next;
	}

	*item_ptr = current->item;
	return 0;
}

int list_pretty_print(struct list *lst) {
	if(NULL == lst) return 1;
	if(NULL == lst->item_print) return 2;

	printf("[");
	if(0 == lst->length) {
		printf("]\n");
		return 0;
	}

	struct list_node *current = lst->front;
	for(int i = 0; i < lst->length - 1; i++) {
		lst->item_print(current->item);
		current = current->next;
		printf(", ");
	}

	lst->item_print(current->item);
	printf("]\n");

	return 0;
}

