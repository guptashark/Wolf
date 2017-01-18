#include <stdio.h>
#include <assert.h>
#include "bstree.h"

int bst_key_cmp(void *a, void *b) {
	(void)a;
	(void)b;
	return 0;
}

int main(void) {

	int result = 0;

	/* test for proper arg checking in bst_init */
	{
		struct bstree *sample_bst = (struct bstree *)10;
		struct bstree **bst_ptr = &sample_bst;
		result = bstree_init(bst_ptr, bst_key_cmp);
		assert(1 == result);
	}

	/* test for proper checking in bst_init key_cmp_fn */
	result = 0;

	{	
		struct bstree *sample_bst = NULL;
		struct bstree **bst_ptr = &sample_bst;
		result = bstree_init(bst_ptr, NULL);
		assert(2 == result);
	}

	/* TODO mem tests to be made after creating custom mem module */
	printf("All tests passed.\n");
	return 0;
}
