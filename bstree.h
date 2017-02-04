


struct bstree;

int bstree_init(
		struct bstree **bst_ptr,
	       	int (*key_cmp)(void *, void *),
		int (*key_printer)(void *),
		int (*val_printer)(void *));

int bstree_insert(struct bstree *bst, void *key, void *val);

int bstree_lookup(struct bstree *bst, void *key, void **val_ptr);

int bstree_pretty_print(struct bstree *bst);
