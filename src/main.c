#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdalign.h>
#include <limits.h>
#include <string.h>

#include <debug.h>
#include <typesys.h>


int main()
{
	object_t * obj = object_create(TYPE_AGGREGATE, "nigger");
	object_add_member(obj, object_create(TYPE_PRIMITIVE|PRIM_INT, "a", 123));
	object_add_member(obj, object_create(TYPE_PRIMITIVE|PRIM_INT, "b", 557));
	object_add_member(obj, object_create(TYPE_PRIMITIVE|PRIM_INT, "c", 12));

	

	object_destroy(obj);
	return 0;
}
