#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dfa.h"

int broken(int err) {
	printf("error is %d.\n", err);
	return 0;
}

int main(void) {

	struct dfa *d1 = NULL;
	int err = dfa_init(&d1);

	if(err) {
		broken(err);
		return 0;
	}

	/* states to add in. */
	char state_names[16][16] = {
		"A",
		"B",
		"C",
		"D",
		"E",
		"F"
	};


	for(int i = 0; i < 6; i++) {
		err = dfa_add_state(d1, state_names[i]);
		if(err) {
			broken(err);
			return 0;
		}
	}

	dfa_set_start(d1, "A");
	dfa_set_final(d1, "E");


	int err2 = 0;
	err2 = dfa_add_transition(d1, "A", "B", "b");
	if(err2) {
		printf("%d is err in add transition\n", err2);
	}
	dfa_add_transition(d1, "B", "C", "c");
	dfa_add_transition(d1, "C", "D", "d");
	dfa_add_transition(d1, "D", "E", "e");

	char inputs[10][10] = {
		"bcde",
		"bcdf",
		"bdg",
	};

	bool result = false;


	for(int i =0 ; i < 3; i++) {
		dfa_compute(d1, inputs[i], &result);
		if(result) {
			printf("Accepted\n");
		} else {
			printf("Rejected\n");
		}
	}


	printf("dfa_tester done testing.\n");
	return 0;
}
