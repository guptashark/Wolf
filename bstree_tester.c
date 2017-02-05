#include <stdio.h>
#include <assert.h>
#include "bstree.h"

int bst_key_cmp(void *a, void *b) {
	int *a_val = (int *)a;
	int *b_val = (int *)b;

	if(*a_val > *b_val) {
		return 1;
	} else if(*a_val < *b_val) {
		return -1;
	} else {
		return 0;
	}
}

int num_printer(void *a) {

	int *a_val = (int *)a;
	printf("%d", *a_val);
	return 0;
}

int char_printer(void *c) {
	char *c_val = (char *)c;
	printf("%c", *c_val);
	return 0;
}

int main(void) {

	int result = 0;

	/* test for proper arg checking in bst_init */
	{
		struct bstree *sample_bst = (struct bstree *)10;
		struct bstree **bst_ptr = &sample_bst;
		result = bstree_init(bst_ptr, bst_key_cmp, NULL, NULL);
		assert(1 == result);
	}

	/* test for proper checking in bst_init key_cmp_fn */
	result = 0;

	{	
		struct bstree *sample_bst = NULL;
		struct bstree **bst_ptr = &sample_bst;
		result = bstree_init(bst_ptr, NULL, NULL, NULL);
		assert(2 == result);
	}

	/* TODO mem tests to be made after creating custom mem module */

	{
		struct bstree *sample_bst = NULL;
		struct bstree **bst_ptr = &sample_bst;
		result = bstree_init(bst_ptr, bst_key_cmp, num_printer, char_printer);

		int arr_keys[] = {20, 10, 5, 8, 19, 18, 12};
		char arr_vals[]= {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

		for(int i = 0; i < 7; i++) {
			int retval = 0;
			retval = bstree_insert(sample_bst, &arr_keys[i], &arr_vals[i]);
			// printf("%d is retval\n", retval);
		}
		
		int err = bstree_pretty_print(sample_bst);
		// printf("%d is err on prettyprint\n", err);
		(void)err;
	}
	printf("All tests passed.\n");
	return 0;
}
