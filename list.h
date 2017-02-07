
struct list;

/* Can have both item_cmp and item_print as null, 
 * in the case where we're storing objects of different types. 
 */
int list_init(
	struct list **lst_ptr, 
	int (*item_cmp)(void *, void *), 
	int (*item_print)(void *));

int list_push_front(struct list *lst, void *item);

int list_push_back(struct list *lst, void *item);

int list_pretty_print(struct list *lst);

