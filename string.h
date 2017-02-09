#include <stdbool.h>

struct string;

/* If there is a NULL for s, creates an empty string.*/
int string_init(struct string **str_ptr, char *s);

int string_has_char(struct string *str, char c, bool *result);

int string_length(struct string *str, int *len_ptr);

int string_concatenate(struct string *str1, struct string *str2);

int string_compare(struct string *str1, struct string *str2, int *result);

int string_char_at(struct string *str, int index, char *ch_ptr);

int string_pretty_print(struct string *str);



