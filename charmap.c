#include <stdio.h>
#include <stdlib.h>

#include "custom_mem.h"
#include "charmap.h"

/* TODO
 * define 256 as a macro in some header
 */
struct charmap {
	void *vals[NUM_CHARS];
	int (*vals_printer)(void *);
};

int
charmap_init(struct charmap **cm_ptr, int (*vals_printer)(void *)) {
	if(NULL == cm_ptr) return 1;
	if(NULL != *cm_ptr) return 2;

	struct charmap *ret = NULL;
	ret = custom_malloc(sizeof(struct charmap));
	if(NULL == ret) return 3;

	for(int i = 0; i < NUM_CHARS; i++) ret->vals[i] = NULL;

	ret->vals_printer = vals_printer;
	*cm_ptr = ret;

	return 0;
}

/* TODO
 * it would be best to use a string iterator to do this. 
 * but for now... since I don't want to implement a string
 * iterator, it seems best to go with just a "char *". 
 */
int charmap_insert(struct charmap *cm, struct string *s, void *val) {
	(void)cm;
	(void)s;
	(void)val;
	return 0;
}

int charmap_c_str_insert(struct charmap *cm, char *s, void *val) {
	if(NULL == cm) return 1;
	if(NULL == s) return 2;
	if(NULL == val) return 3;

	/* while we're using a hacky sort of strlen, 
	 * I don't want to start mixing up string.h 
	 * standard lib and string.h my lib. 
	 */

	/* right now, trust that the string doesn't end, 
	 * or go past 128, because then there's a problem.
	 */

	for(int i = 0; s[i] != '\0'; i++) {

		if(i > 127) {
			printf("weird issue in charmap c_str_insert.\n");
			return 4;
		}

		char c = s[i];
		if(cm->vals[c] != NULL) {
			printf("overwriting issue in charmap c_str_insert.\n");
			return 5;
		}

		cm->vals[c] = val;
	}

	return 0;

}
	

/* TODO
 * what should the function checking be on the char? 
 */
int charmap_lookup(
	struct charmap *cm, 
	char c,
	void **val_ptr)
{
	if(NULL == cm) return 1;
	if(NULL == val_ptr) return 3;
	if(NULL != *val_ptr) return 4;

	*val_ptr = cm->vals[c];

	return 0;
}

/* TODO implement this. 
 * right now, it seems a little hard
 * and is really only for testing. 
 */


int charmap_pretty_print(struct charmap *cm) {
	if(NULL == cm) return 1;
	//if(NULL == cm->vals_printer) return 2;
/*
	char s[256];
	char seen[256];
	for(int i =0 ; i < 256; i++) {
		s[i] = '\0';
		seen[i] = 'n';
	}

	void *current = NULL;

	for(int i = 0; i < NUM_CHARS; i++) {
		current = cm->vals[i];

		for(int j = 0; j < NUM_CHARS; j++) {
			if(cm->vals[i]
*/

	for(char c = 'a'; c < 'g'; c++) {
		printf("%c: %p\n", c, cm->vals[c]);
	}
	return 0;
}

	


