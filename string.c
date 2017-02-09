#include <stdlib.h>
#include <stdio.h>

#include "custom_mem.h"
#include "string.h"

struct string {
	int length;
	int capacity;

	char *vals;
};

int
string_init(struct string **str_ptr, char *s) {

	if(NULL == str_ptr) return 1;
	if(NULL != *str_ptr) return 2;

	struct string *ret = NULL;
	ret = custom_malloc(sizeof(struct string));

	if(NULL == ret) return 1;

	if(s == NULL) {
		ret->length = 0;
		ret->capacity = 8;
		ret->vals = custom_malloc(sizeof(char) * ret->capacity);

		if(NULL == ret->vals) {
			custom_free(ret);
			return 3;
		}

		*str_ptr = ret;
		return 0;
	} 
	
	int s_length = 0;
	for(int i =0; s[i] != '\0'; i++) s_length++;

	int quotient = s_length / 8;
	ret->capacity = (quotient + 1) * 8;
	
	ret->vals = custom_malloc(sizeof(char) * ret->capacity);

	if(NULL == ret->vals) {
		custom_free(ret);
		return 3;
	}

	ret->length = s_length;
	for(int i =0; i < ret->length; i++) ret->vals[i] = s[i];
	*str_ptr = ret;
	
	return 0;
}

int string_has_char(struct string *str, char c, bool *result) {
	if(NULL == str) return 1;
	if(0 == str->length) *result = false;

	for(int i = 0; i < str->length; i++) {
		if(str->vals[i] == c) {
			*result = true;
			return 0;
		}
	}

	*result = false;
	return 0;
}

int string_length(struct string *str, int *len_ptr) {
	if(NULL == str) return 1;
	if(NULL == len_ptr) return 2;

	*len_ptr = str->length;
	return 0;
}

int string_concatenate(struct string *str1, struct string *str2) {
	
	if(NULL == str1) return 1;
	if(NULL == str2) return 2;

	if(str1->length + str2->length > str1->capacity) {
		int quotient = (str1->length + str2->length) / 8;
		str1->capacity = (quotient + 1) * 8;
		char *bigger_val = custom_malloc(sizeof(char) * str1->capacity);
		if(NULL == bigger_val) {
			return 3;
		}

		for(int i = 0; i < str1->length; i++) {
			bigger_val[i] = str1->vals[i];
		}

		for(int i = 0; i < str2->length; i++) {
			bigger_val[i + str1->length] = str2->vals[i];
		}

		custom_free(str1->vals);
		str1->vals = bigger_val;
	} else {
		for(int i =0 ; i < str2->length; i++) {
			str1->vals[i + str1->length] = str2->vals[i];
		}
	}

	str1->length = str1->length + str2->length;

	return 0;
}

int string_compare(struct string *str1, struct string *str2, int *result) {
	if(NULL == str1) return 1;
	if(NULL == str2) return 2;

	int min_length = 0;
	int longer_str = 0;

	if(str1->length > str2->length) {
		min_length = str2->length;
		longer_str = 1;
	} else if(str1->length < str2->length) {
		min_length = str1->length;
		longer_str = 2;
	} else {
		min_length = str1->length;
		longer_str = 0;
	}

	for(int i = 0; i < min_length; i++) {
		if(str1->vals[i] > str2->vals[i]) {
			*result = 1;
			return 0;
		} else if(str1->vals[i] < str2->vals[i]) {
			*result = -1;
			return 0;
		}
	}

	if(longer_str == 0) {
		*result = 0;
	} else if(longer_str == 1) {
		*result = 1;
	} else if(longer_str == 2) {
		*result = -1;
	}

	return 0;
}	

int
string_char_at(struct string *str, int index, char *ch_ptr) {
	if(NULL == str) return 1;
	if(index < 0) return 2;
	if(index >= str->length) return 3;
	if(NULL == ch_ptr) return 4;

	*ch_ptr = str->vals[index];
	return 0;
}


int
string_pretty_print(struct string *str) {
	if(NULL == str) return 1;

	printf("\"");
	for(int i = 0; i < str->length; i++) {
		printf("%c", str->vals[i]);
	}
	printf("\"");
	return 0;
}
