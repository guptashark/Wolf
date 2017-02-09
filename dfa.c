#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "bstree.h"
#include "string.h"
#include "custom_mem.h"
#include "charmap.h"

/* 
 * every character, move a state. 
 * Decide which state to go to. 
 * Each state has a dict. 
 * 	keys are strings, values are pointers to other states. 
 * 	the dfa keeps track of the current state. 
 *
 * Build the dfa automatically
 * 	A process best left for some other time. 
 */

struct dfa_state {
	struct string *state_name;	
	struct charmap *transitions;

};

/* TODO 
 * This function is really just for debugging, but should work. 
 * We may later add on something like printing the dictionary too. 
 */
int print_dfa_state(struct dfa_state *to_print) {
	if(NULL == to_print) return 1;

	string_pretty_print(to_print->state_name);
	return 0;
};

static
int 
dfa_state_init(
	struct dfa_state **dfa_state_ptr,
	struct string *state_name)
{
	if(NULL == dfa_state_ptr) return 1;
	if(NULL != *dfa_state_ptr) return 2;
	if(NULL == state_name) return 3;

	struct dfa_state *ret = NULL;
	ret = custom_malloc(sizeof(struct dfa_state));
	if(NULL == ret) {
		return 4;
	}

	ret->state_name = state_name;

	struct charmap *cm = NULL;
	int err = charmap_init(&cm, NULL);
	if(err) {
		printf("issue in dfa_state_init\n");
		return 5;
	}

	ret->transitions = cm;

	*dfa_state_ptr = ret;
	return 0;
}

static 
int
dfa_state_step(struct dfa_state *ds, char c, struct dfa_state **next_ptr) {
	if(NULL == ds) return 1;
	if(NULL == next_ptr) return 2;
	if(NULL != *next_ptr) return 3;

	struct dfa_state *next = NULL;
	int err = 0;
	err = charmap_lookup(ds->transitions, c, &next);
	if(err) {
		printf("Fatal error in dfa_state_step.\n");
		return 4;
	}

	*next_ptr = next;
	return 0;
}


struct dfa {

	struct bstree *state_map;
	struct dfa_state *start_state;	

	/* list of dfa_state pointers */
	struct list *final_states;
};

static int ptr_cmp(void *a, void *b, int *res) {
	if(a == b) {
		*res = 0;
	} else {
		*res = 1;
	}

	return 0;
}


int dfa_init(struct dfa **dfa_ptr) {
	if(NULL == dfa_ptr) return 1;
	if(NULL != *dfa_ptr) return 2;

	int err = 0;

	struct dfa *ret = custom_malloc(sizeof(struct dfa));
	if(NULL == ret) return 3;

	struct bstree *states = NULL;
	err = bstree_init(&states, string_compare, NULL, NULL);
	if(err) {
		/* TODO take action here. */
		printf("break in dfa_init\n");
		return 4;
	}

	struct list *final_states = NULL;
	err = list_init(&final_states, ptr_cmp, print_dfa_state);
	if(err) {
		/* TODO take action here */
		printf("break in dfa_init, second list init.\n");
		return 4;
	}

	ret->state_map = states;
	ret->final_states = final_states;
	*dfa_ptr = ret;

	return 0;
}

int dfa_add_state(struct dfa *automata, char *state_name) {
	if(NULL == automata) return 1;
	if(NULL == state_name) return 2;

	struct string *name = NULL;
	int err = string_init(&name, state_name);
	if(err) {
		/* TODO take action here */
		printf("fatal error 3 in dfa_add_state.\n");
		return 3;
	}

	struct dfa_state *to_add = NULL;
	err = dfa_state_init(&to_add, name);
	if(err) {
		/* TODO take action here */
		printf("fatal error 4 in dfa_add state.\n");
		return 4;
	}

	err = bstree_insert(automata->state_map, name, to_add);
	if(err) {
		/* TODO take action here */
		printf("fatal error 5 in dfa_add_state.\n");
		return 5;
	}

		
	return 0;
}

/* TODO
 * Is there a special way this should be called? 
 * As in, should it look in the set of states, to see if
 * it already exists... or... 
 *
 * As of right now, assume that the start state exists
 * in our set of states. 
 * Search for the state, and get a pointer to it. 
 * Set that pointer to the start state. 
 */
int dfa_set_start(struct dfa *automata, char *state_name) {
	if(NULL == automata) return 1;
	if(NULL == state_name) return 2;

	struct string *name_str = NULL;
	int err = string_init(&name_str, state_name);
	if(err) {
		/* TODO take action here */
		printf("fatal error 3 in dfa_set_start.\n");
		return 3;
	}

	struct dfa_state *to_set = NULL;
	err = bstree_lookup(automata->state_map, name_str, &to_set);
	if(err) {
		/* TODO take action here */
		printf("fatal error 3 in dfa_set_start.\n");
		return 4;
	}

	automata->start_state = to_set;
	return 0;
}

/* TODO
 *
 * As of right now, same assumptions as in the start state fn, 
 * Search for the state in the list of states, 
 * add the pointer to the list of final states. 
 *
 * A further improvement might be to make the list of final 
 * states into a bstree, for faster checking, for potentially
 * larger DFA's. 
 */
int dfa_set_final(struct dfa *automata, char *state_name) {
	if(NULL == automata) return 1;
	if(NULL == state_name) return 2;

	struct string *name_str = NULL;
	int err = string_init(&name_str, state_name);
	if(err) {
		/* TODO */
		printf("fatal error 3 in dfa_set_final.\n");
		return 3;
	}

	struct dfa_state *to_set = NULL;
	err = bstree_lookup(automata->state_map, name_str, &to_set);
	if(err) {
		/* TODO */
		printf("fatal error 4 in dfa_set_final.\n");
		return 4;
	}

	list_push_front(automata->final_states, to_set);
	return 0;
}

int dfa_add_transition(
	struct dfa *automata, 
	char *from_state,
	char *to_state,
	char *symbols)
{
	if(NULL == automata) return 1;
	if(NULL == from_state) return 2;
	if(NULL == to_state) return 3;
	if(NULL == symbols) return 4;

	struct dfa_state *from_ptr = NULL;
	struct dfa_state *to_ptr = NULL;

	int err = 0;

	struct string *from_str = NULL;
	struct string *to_str = NULL;

	string_init(&from_str, from_state);
	string_init(&to_str, to_state);

	err = bstree_lookup(automata->state_map, from_str, &from_ptr);
	if(err) {
		printf("Fatal error in dfa_add transition.\n");
		return 5;
	}

	err = bstree_lookup(automata->state_map, to_str, &to_ptr);
	if(err) {
		printf("Fatal error code 6 in dfa_add_transition.\n");
		return 6;
	}

	if(to_ptr == NULL) {
		printf("didn't find ");
		string_pretty_print(to_str);
		printf(" in the bstree\n");
	}
	
	err = charmap_c_str_insert(from_ptr->transitions, symbols, to_ptr); 
	if(err) {
		printf("Fatal error code 7 in dfa_add_transition.\n");
		printf("err is; %d\n", err);
		return 7;
	}

	return 0;
}

/* need to add more here... 
 * TODO
 */
int dfa_compute(struct dfa *automaton, char *input, bool *accept_ptr) {

	struct dfa_state *current = automaton->start_state;

	struct dfa_state *next = NULL;
	for(int i =0; input[i] != '\0'; i++) {
		//string_pretty_print(current->state_name);
		//printf(": with symbol %c\n: ", input[i]);
		///charmap_pretty_print(current->transitions);
		dfa_state_step(current, input[i], &next);
		if(NULL == next) {
			*accept_ptr = false;
			return 0;

		}
		current = next;
		next = NULL;
	}

	//string_pretty_print(current->state_name);
	//printf(" is the ending state.\n");
	bool is_final = false;
	list_contains(automaton->final_states, current, &is_final);

	if(is_final) {
		*accept_ptr = true;
	} else {
		*accept_ptr = false;
	}

	return 0;
}


int dfa_pretty_print(struct dfa *automaton) {
	if(NULL == automaton) return 1;

	print_dfa_state(automaton->start_state);
	printf("\n");

	list_pretty_print(automaton->final_states);
	printf("\n");
	return 0;
}




