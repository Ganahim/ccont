#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <func_stack_t.h>
#include <ptr_stack_t.h>
#include <buffer_t.h>

void f1() { printf("f1\n"); }
void f2() { printf("f2\n"); }
void f3() { printf("f3\n"); }


int main()
{
	buffer_t * buf = buffer_create(0, 256);

	for(size_t i = 0; i < 50000; i++) {
		buffer_resize(buf, buf->size + 8);
	}

	// buffer_resize(buf, sizeof(function_t) * 3);
	// function_t * p = buffer_begin(buf);
	// *p = f1; p++;
	// *p = f2; p++;
	// *p = f3; p++;
	//
	// for(function_t * ppf = buffer_begin(buf); ppf != buffer_end(buf); ppf++) {
	// 	(*ppf)();
	// }


	buffer_debug(buf);
	buffer_destroy(buf);
	return 0;
}
