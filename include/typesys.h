#ifndef _TYPESYS_H
#define _TYPESYS_H

#include <stdint.h>


union _PRIM_VALUE_T;
struct _OBJECT_T;
struct _PTR_STACK_T;


/* Type representation
	15:12			Type category
	11:8			Pointer level
	8:0			Extra info
*/


enum {
	TYPE_PRIMITIVE 	= 0x0000,
	TYPE_POINTER		= 0x1000,
	TYPE_FUNCTION		= 0x2000,
	TYPE_AGGREGATE		= 0x3000
};

/* Primitive types */
enum {
	PRIM_VOID = 0,
	PRIM_CHAR,
	PRIM_SCHAR,
	PRIM_SHORT,
	PRIM_INT,
	PRIM_LONG,
	PRIM_LONGLONG,
	PRIM_UCHAR,
	PRIM_USHORT,
	PRIM_UINT,
	PRIM_ULONG,
	PRIM_ULONGLONG,
	PRIM_BOOL,
	PRIM_FLOAT,
	PRIM_DOUBLE,
	PRIM_LONGDOUBLE
};



typedef union _PRIM_VALUE_T {
	char c;

	signed char sc;
	short s;
	int i;
	long l;
	long long ll;

	unsigned char uc;
	unsigned short us;
	unsigned int ui;
	unsigned long ul;
	unsigned long long ull;
	_Bool b;

	float f;
	double d;
	long double ld;
} prim_value_t;




typedef struct _OBJECT_T * (*pfn_generic_t)(struct _OBJECT_T **);

typedef struct _OBJECT_T {
	uint16_t type;
	char * name;

	union {
		prim_value_t prim;
		void * ptr;
		pfn_generic_t func;
		struct _PTR_STACK_T * memb;
	};
} object_t;


object_t * object_create(uint16_t type, const char * name, ...);
void object_destroy(object_t * obj);

void object_add_member(object_t * obj, object_t * other);


int object_memb_dtor(void * memb);

#endif
