#include <stdlib.h>

#include "custom_mem.h"

void *custom_malloc(size_t s) {
	return malloc(s);
}

void custom_free(void *p) {
	free(p);
}

