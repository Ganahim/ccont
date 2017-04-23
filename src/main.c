#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <buffer_t.h>
#include <util.h>
#include <ptr_stack_t.h>
#include <func_stack_t.h>


int main()
{
	ptr_stack_t * s = ptr_stack_create();

	for(size_t i = 0; i < 1000000; i++) {
		ptr_stack_push(s, "nigger");
	}

	ptr_stack_destroy(s);
	return 0;
}
