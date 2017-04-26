#include <assert.h>
#include <branch_t.h>

int branch_exec(branch_t * branch) {
	assert(branch != NULL);
	assert(branch->pred != NULL);
	assert(branch->action != NULL);

	if(branch->branch_type == BRANCH_IF) {
		if(branch->pred(branch->data)) {
			branch->action_ret = branch->action(branch->data);
		}
	}
	else if(branch->branch_type == BRANCH_WHILE) {
		while(branch->pred(branch->data)) {
			branch->action_ret = branch->action(branch->data);
		}
	}

	return 0;
}
