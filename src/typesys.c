#include <stdarg.h>
#include <containers_common.h>
#include <ptr_stack_t.h>
#include <util.h>
#include <typesys.h>
#include <debug.h>


object_t * object_create(uint16_t type, const char * name, ...) {
	assert(name != NULL);

	uint16_t typeCat 	= type & 0xF000;
	uint16_t ptrLevel = (type & 0x0F00) >> 8;
	uint16_t extra 	= type & 0x00FF;

	object_t * obj;
	char * nameBuf;

	va_alloc(
		(void **)&obj, sizeof(object_t),
		(void **)&nameBuf, strlen(name)+1
	);

	strcpy(nameBuf, name);
	obj->name = nameBuf;
	obj->type = type;


	va_list ap;
	va_start(ap, name);

	switch(typeCat) {
		case TYPE_PRIMITIVE:
			switch(extra) {
				case PRIM_VOID:
					break;
				case PRIM_CHAR:			obj->prim.c = va_arg(ap, int); break;
				case PRIM_SCHAR:			obj->prim.sc = va_arg(ap, int); break;
				case PRIM_SHORT:			obj->prim.s = va_arg(ap, int); break;
				case PRIM_INT:				obj->prim.i = va_arg(ap, int); break;
				case PRIM_LONG:			obj->prim.l = va_arg(ap, long); break;
				case PRIM_LONGLONG:		obj->prim.ll = va_arg(ap, long long); break;
				case PRIM_UCHAR:			obj->prim.uc = va_arg(ap, unsigned int); break;
				case PRIM_USHORT:			obj->prim.us = va_arg(ap, unsigned int); break;
				case PRIM_UINT:			obj->prim.ui = va_arg(ap, unsigned int); break;
				case PRIM_ULONG:			obj->prim.ul = va_arg(ap, unsigned long); break;
				case PRIM_ULONGLONG:		obj->prim.ull = va_arg(ap, unsigned long long); break;
				case PRIM_BOOL:			obj->prim.b = va_arg(ap, int); break;
				case PRIM_FLOAT:			obj->prim.f = va_arg(ap, double); break;
				case PRIM_DOUBLE:			obj->prim.d = va_arg(ap, double); break;
				case PRIM_LONGDOUBLE:	obj->prim.ld = va_arg(ap, long double); break;
				default:
					abort();
			}
			break;
		case TYPE_POINTER:
			obj->ptr = va_arg(ap, void *);
			break;
		case TYPE_FUNCTION:
			obj->func = va_arg(ap, pfn_generic_t);
			break;
		case TYPE_AGGREGATE:
			obj->memb = ptr_stack_create(0, 256);
			obj->memb->destroy_hook = object_memb_dtor;
			break;
		default:
			abort();
	}

	va_end(ap);
	return obj;
}

void object_destroy(object_t * obj) {
	assert(obj != NULL);
	FUNC_DEBUG("");

	uint16_t typeCat = obj->type & 0xF000;

	switch(typeCat) {
		case TYPE_PRIMITIVE:
		case TYPE_POINTER:
		case TYPE_FUNCTION:
			break;
		case TYPE_AGGREGATE:
			ptr_stack_destroy(obj->memb);
			break;
	}

	FREE(obj);
}


int object_memb_dtor(void * vp_memb) {
	assert(vp_memb != NULL);

	ptr_stack_t * memb = vp_memb;

	for(void ** p = ptr_stack_begin(memb); p != ptr_stack_end(memb); p++) {
		object_destroy((object_t *)*p);
	}

	return 0;
}


void object_add_member(object_t * obj, object_t * other) {
	assert(obj != NULL);
	assert(other != NULL);
	assert((obj->type & 0xF000) == TYPE_AGGREGATE);

	ptr_stack_push(obj->memb, other);
}
