#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

int foo(void *a, void *b) {
	(void)a;
	(void)b;
	return 0;
}

int main(int argc, char *argv[]) {

	(void)argc;
	(void)argv;

	bst_lib_set_custom_malloc(malloc);

	struct bstree *bst1 = NULL;
	struct bstree **bst_ptr = &bst1;

	int result = bstree_init(bst_ptr, foo);
	if(result) {
		printf("err code: %d\n", result);
	}

	printf("end of main\n");
	


	return 0;
}
