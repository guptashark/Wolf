#include <stdio.h>

#include "list.h"

int print_str(void *s) {
	char *str = (char *)s;
	printf("%s", str);
	return 0;
}

int main(void) {


	char str_array[16][16] = {
		"Harry", 
		"Hermione",
		"Ron",
		"Neville",
		"Severus",
		"Dumbledore",
		"Malfoy"
	};

	struct list *lst = NULL;
	list_init(&lst, NULL, print_str);


	for(int i = 0; i < 7; i++) {
		list_pretty_print(lst);
		list_push_front(lst, str_array[i]);
	}

	list_pretty_print(lst);
	char *herb = NULL;
	list_access(lst, 3, &herb);
	print_str(herb);
	printf("\n");
	herb = NULL;
	list_pop_front(lst, &herb);
	print_str(herb);
	printf("\n");
	list_pretty_print(lst);

	return 0;
}

	


