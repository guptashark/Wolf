#include "string.h"
#include <stdbool.h>
/*
struct dfa;

init

add_state

add_start_state

add_final_state

add_transition
	search for states with associated names. 
	Add in the transition. 

run_through
	just use the pointers in the states. 

*/

/* Library notes:
 *
 * Currently, the library works by assuming someone will be giving 
 * in C style strings for all the functions to do things. 
 *
 * The dfa then uses the string library for its internals. 
 * We can add in "adapters" in case the caller is using the string lib, 
 * or just add in a function that turns strings into c_srings. 
 *
 * Right now, we'll stick with the library taking the basic C_string. 
 */

struct dfa;

int dfa_build_from_file(struct dfa **dfa_ptr, FILE *f, struct string *file_type);

int dfa_init(struct dfa **dfa_ptr);

int dfa_add_state(struct dfa *automata, char *state_name);

int dfa_set_start(struct dfa *automata, char *state_name);

int dfa_set_final(struct dfa *automata, char *state_name);

int dfa_add_transition(
	struct dfa *automata, 
	char *from_state, 
	char *to_state, 
	char *symbols);

int dfa_compute(struct dfa *automata, char *input, bool *accept_ptr);

int dfa_pretty_print(struct dfa *automaton);
