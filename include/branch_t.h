#ifndef _BRANCH_T_H
#define _BRANCH_T_H

/* Experimental object type for storing a branching 'instruction'.

*/



#include <containers_common.h>

enum {
	BRANCH_IF,
	BRANCH_WHILE
};


typedef struct _BRANCH_T {
	size_t branch_type;
	int (*pred)(void *);
	void * data;
	void * (*action)(void *);
	void * action_ret;
	struct _BRANCH_T * next;		// else, else if
} branch_t;


int branch_exec(branch_t * branch);




#endif
