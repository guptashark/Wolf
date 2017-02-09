#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "custom_mem.h"
#include "bstree.h"

struct bst_node {
	void *key;
	void *val;
	struct bst_node *left_child;
	struct bst_node *right_child;
};

/* TODO which values get to be consted? 
 *
 * Purpose: 
 * 	Create a bst_node with a key. 
 *
 * Errors: 
 * 	1: the bst_node_ptr is null. 
 * 	2: the pointer bst_node_ptr points to isn't null. 
 * 	3: the key is null. 
 *	4: out of memory. 
 */	
static
int
bst_node_init(
	struct bst_node **bst_node_ptr,
	void *key)
{
	if(NULL == bst_node_ptr) return 1;
	if(NULL != *bst_node_ptr) return 2;
	if(NULL == key) return 3;

	struct bst_node *ret = NULL;
	ret = custom_malloc(sizeof(struct bst_node));

	if(NULL == ret) return 4;

	ret->key = key;
	ret->left_child = NULL;
	ret->right_child = NULL;
	*bst_node_ptr = ret;
	return 0;
}	

struct bstree {
	struct bst_node *root;
	int (*key_cmp)(void *, void *, int *);
	int (*key_printer)(void *);
	int (*val_printer)(void *);
};

int 
bstree_init(
	struct bstree **bst_ptr, 
	int (*key_cmp)(void *, void *, int *),
	int (*key_printer)(void *),
	int (*val_printer)(void *))
{

	if(NULL != *bst_ptr) return 1;
	if(NULL == key_cmp) return 2;

	struct bstree *new_bst = custom_malloc(sizeof(struct bstree));

	if(new_bst == NULL) return 3;

	new_bst->root = NULL;
	new_bst->key_cmp = key_cmp;
	new_bst->key_printer = key_printer;
	new_bst->val_printer = val_printer;
	*bst_ptr = new_bst;

	return 0;
}


/* Purpose: 
 * 	This fn returns the node associated with a key. 
 * 	If the node doesn't exist, but create_node is true, 
 * 	the node is created, attached to the tree and a pointer
 * 	to the node is put into ptr_bst_node. If create_node is 
 * 	false, then ptr_bst_node will be a pointer to a NULL. 
 *
 * 	This fn is useful as a helper to bstree_insert
 * 	and bstree_lookup. bstree_insert will call the function 
 * 	with create_node as true, while lookup will call the fn
 * 	with create_node as false. 
 *
 * Errors: 
 * 	1: bst is null. 
 * 	2: key is null. 
 * 	3: the pointer to the node pointer is null. 
 * 	4: the pointer that ptr_bst_node points to is not null. 
 * 	5: the bst->key_cmp fn returned a val not in set {-1, 0, 1}
 * 	6: error from bst_node_init. 
 *
 */
static 
int 
bstree_internal_lookup(
	struct bstree *bst, 
	void *key, 
	struct bst_node **ptr_bst_node,
	bool create_node)
{
	if(bst == NULL) return 1;
	if(key == NULL) return 2;
	if(ptr_bst_node == NULL) return 3;
	if(*ptr_bst_node != NULL) return 4;

	int err = 0;
	struct bst_node *previous = bst->root;
	
	if(previous == NULL) {

		if(!create_node) return 0;

		err = bst_node_init(&previous, key);
		if(err) {
			printf("error in bst_node_init, code = %d\n", err);
			return 6;
		}
		
		*ptr_bst_node = previous;
		bst->root = previous;
		return 0;
	}

	int cmp_result = 0;
	struct bst_node *current = bst->root;

	err = bst->key_cmp(key, previous->key, &cmp_result);
	if(err) {
		printf("err in bil, %d\n", err);
	}

	if(cmp_result == 0) {
		*ptr_bst_node = previous;
		return 0;
	} else if(cmp_result == 1) {
		current = previous->right_child;
	} else if(cmp_result == -1) {
		current = previous->left_child;
	} else {
		return 5;
	}

	while(current != NULL) {
		cmp_result = 0;
		bst->key_cmp(key, current->key, &cmp_result);

		if(cmp_result == 0) {
			*ptr_bst_node = current;
			return 0;
		} else if(cmp_result == 1) {
			previous = current;
			current = current->right_child;
		} else if(cmp_result == -1) {
			previous = current;
			current = current->left_child;
		} else {
			return 5;
		}
	}

	if(!create_node) return 0;

	struct bst_node *to_add = NULL;	
	err = 0;
	err = bst_node_init(&to_add, key);

	if(err) {
		printf("Error in bst_node_init, code: %d\n", err);
		return 6;
	}
	
	if(1 == cmp_result) {
		previous->right_child = to_add;
	} else {
		previous->left_child = to_add;
	}

	*ptr_bst_node = to_add;
	return 0;
}	

int 
bstree_insert(
	struct bstree *bst, 
	void *key, 
	void *val) 
{
	if(NULL == bst) return 1;
	if(NULL == key) return 2;
	if(NULL == val) return 3;

	struct bst_node *node = NULL;
	int err = bstree_internal_lookup(bst, key, &node, true);
	// printf("err is %d in insert, on internal lookup\n", err);
	(void)err;

	if(node == NULL) return 1;

	node->val = val;
	return 0;

}

int bstree_lookup(
	struct bstree *bst,
	void *key,
	void **val_ptr) 
{
	if(bst == NULL) return 1;
	if(key == NULL) return 2;
	if(val_ptr == NULL) return 3;
	if(*val_ptr != NULL) return 4;

	struct bst_node *node = NULL;
	int err = bstree_internal_lookup(bst, key, &node, false);

	if(err) {
		printf("err in lookup: %d\n", err);
	}
			

	if (node != NULL) *val_ptr = node->val;
	return 0;
} 

static
int 
bst_node_pretty_print(
		struct bst_node *node,
		int (*key_printer)(void *),
		int (*val_printer)(void *))

{
	if(NULL == node) return 0;
	if(NULL == key_printer) return 1;
	if(NULL == val_printer) return 2;

	bst_node_pretty_print(node->left_child, key_printer, val_printer);
	key_printer(node->key);
	printf(": ");
	val_printer(node->val);
	bst_node_pretty_print(node->right_child, key_printer, val_printer);

	return 0;
}


int bstree_pretty_print(struct bstree *bst) {
	if(NULL == bst) return 1;
	if(NULL == bst->key_printer) return 2;
	if(NULL == bst->val_printer) return 3;

	bst_node_pretty_print(bst->root, bst->key_printer, bst->val_printer);

	return 0;
}


