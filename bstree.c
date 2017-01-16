#include <stdlib.h>

#include "bstree.h"

static void *(*custom_malloc)(size_t);

int bst_lib_set_custom_malloc(void *(*malloc_fn)(size_t)) {
	custom_malloc = malloc_fn;
	return 0;
}

struct bst_node {
	void *key;
	void *val;
	struct bst_node *left_child;
	struct bst_node *right_child;
};

struct bstree {
	struct bst_node *root;
	int (*key_cmp)(void *, void *);
};

int bstree_init(struct bstree **bst_ptr, int (*key_cmp)(void *, void *)) {

	if(*bst_ptr != NULL) return 1;
	if(key_cmp == NULL) return 2;

	struct bstree *new_bst = custom_malloc(sizeof(struct bstree));

	if(new_bst == NULL) return 3;

	new_bst->root = NULL;
	new_bst->key_cmp = key_cmp;
	*bst_ptr = new_bst;

	return 0;
}

