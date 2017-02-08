#include <stdbool.h>

struct list;

/* Can have both item_cmp and item_print as null, 
 * in the case where we're storing objects of different types. 
 */
int list_init(
	struct list **lst_ptr, 
	int (*item_cmp)(void *, void *, int *), 
	int (*item_print)(void *));

int list_push_front(struct list *lst, void *item);

int list_pop_front(struct list *lst, void **item_ptr);

int list_push_back(struct list *lst, void *item);

int list_length(struct list *lst, int *len_ptr);

int list_contains(struct list *lst, void *item, bool *result);

int list_access(struct list *lst, int index, void **item_ptr);

/* TODO functional list functions. 
 * map
 * filter
 * foldr
 * foldl
 * build_list
 * andmap
 * ormap
 */

int list_pretty_print(struct list *lst);

