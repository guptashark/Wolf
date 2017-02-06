#include <stdio.h>
#include <assert.h>


#include "string.h"

// TODO make it so that the header file is in a subdirectory, so that we don't have naming conflicts. 

int main(void) {

	char *sample_s = "banana";
	struct string *str1 = NULL;

	char *sample_s2 = "banana";
	struct string *str2 = NULL;

	string_init(&str1, sample_s);
	string_init(&str2, sample_s2);

	string_pretty_print(str1);
	printf("\n");
	string_pretty_print(str2);
	printf("\n");

	//string_concatenate(str1, str2);
	string_pretty_print(str1);

	int result = 0;
	string_compare(str1, str2, &result);
	assert(result == 0);

		

	return 0;
}
