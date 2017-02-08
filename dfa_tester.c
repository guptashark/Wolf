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
		"alpha",
		"beta",
		"gamma", 
		"epsilon",
		"phi",
		"chi",
		"sigma"
	};


	for(int i = 0; i < 7; i++) {
		err = dfa_add_state(d1, state_names[i]);
		if(err) {
			printf("in loop: %d\n", i);
			broken(err);
			return 0;
		}
	}

	dfa_set_start(d1, "phi");
	dfa_set_final(d1, "sigma");
	dfa_set_final(d1, "beta");

	dfa_pretty_print(d1);

	printf("dfa_tester done testing.\n");
	return 0;
}
