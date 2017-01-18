


struct bstree;

int bstree_init(struct bstree **bst_ptr, int (*key_cmp)(void *, void *));

int bstree_insert(struct bstree *bst, void *key, void *val);

int bstree_lookup(struct bstree *bst, void *key, void **val_ptr);


