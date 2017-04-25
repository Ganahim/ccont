#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdalign.h>

#include <debug.h>
#include <util.h>
#include <ptr_stack_t.h>

int main()
{
	ptr_stack_t * stack = ptr_stack_create(0, 32);
	ptr_stack_push(stack, "asd");
	ptr_stack_push(stack, "asd");
	ptr_stack_push(stack, "asd");
	ptr_stack_push(stack, "asd");


	ptr_stack_debug(stack);
	ptr_stack_destroy(stack);
	debug_check_diff();
	return 0;
}
