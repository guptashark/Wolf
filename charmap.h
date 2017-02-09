
#define NUM_CHARS 256

#include "string.h"

struct charmap;

int charmap_init(
	struct charmap **cm_ptr, 
	int (*vals_printer)(void *));

int charmap_insert(struct charmap *cm, struct string *s, void *val);

int charmap_c_str_insert(struct charmap *cm, char *s, void *val);

int charmap_lookup(
	struct charmap *cm, 
	char c,
	void **val_ptr);

int charmap_pretty_print(struct charmap *cm);
