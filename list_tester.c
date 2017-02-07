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

	return 0;
}

	


