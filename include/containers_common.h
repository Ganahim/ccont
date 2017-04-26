#ifndef _CONTAINERS_COMMON_H
#define _CONTAINERS_COMMON_H

#ifndef ALLOC
#	define ALLOC(...)		malloc(__VA_ARGS__)
#endif
#ifndef REALLOC
#	define REALLOC(...)	realloc(__VA_ARGS__)
#endif
#ifndef FREE
#	define FREE(...)		free(__VA_ARGS__)
#endif

#include <stddef.h>
#include <stdalign.h>
#include <stdint.h>
#include <assert.h>

/*** Types ***/

/* Memory mgmt function pointers */
typedef void * (*pfn_alloc_t)(size_t);
typedef void * (*pfn_realloc_t)(void *, size_t);
typedef void (*pfn_free_t)(void *);

/* Pointer types for object facilities */
typedef int (*pfn_dtor_t)(void * self);
typedef int (*pfn_copy_t)(void * dest, void * src);
typedef void (*pfn_exception_handler_t)(void * self, int code);






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
	PRIM_LONGDOUBLE,

};

#define MAKE_TYPE(PRIM, PTR_LEVEL)		((PRIM) | ((PTR_LEVEL & 0xF)) << 8)


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


// typedef struct _PRIMITIVE_T {
// 	uint16_t type;
// 	union {
// 		prim_value_t value;
// 		void * ptr;
// 	};
// } primitive_t;

#endif
