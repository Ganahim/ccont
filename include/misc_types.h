#ifndef _MISC_TYPES_H
#define _MISC_TYPES_H

#include <stdint.h>


#define PRIM_TYPE_CHAR		0b00000001
#define PRIM_TYPE_INT		0b00000010
#define PRIM_TYPE_FLOAT		0b00000011

#define PRIM_PTR				0b10000000
#define PRIM_UNSIGNED		0b01000000

#define PRIM_W_8				0b00000100
#define PRIM_W_16				0b00001000
#define PRIM_W_32				0b00001100
#define PRIM_W_64				0b00010000

#define PRIM_FLOAT_SINGLE	0b00000100
#define PRIM_FLOAT_DOUBLE	0b00001000
#define PRIM_FLOAT_EXT		0b00001100



/* Union for primitive types */
typedef struct _PRIMITIVE_T {
	union {

		/* Char */
		union {
			signed char s;
			unsigned char u;
		} c;

		/* Integer */
		union {
			union {
				int8_t b;
				int16_t w;
				int32_t d;
				int64_t q;
			} s;

			union {
				uint8_t b;
				uint16_t w;
				uint32_t d;
				uint64_t q;
			} u;
		} i;

		/* Floating-point */
		union {
			float s;			// single precision
			double d;		// double precision
			long double e;	// extended precision
		} f;


		/* Pointers */
		union {

			/* Pointer to char */
			union {
				signed char * s;
				unsigned char * u;
			} c;

			/* Pointer to integer */
			union {
				union {
					int8_t * b;
					int16_t * w;
					int32_t * d;
					int64_t * q;
				} s;

				union {
					uint8_t * b;
					uint16_t * w;
					uint32_t * d;
					uint64_t * q;
				} u;
			} i;

			/* Pointer to floating-point */
			union {
				float * s;			// single precision
				double * d;			// double precision
				long double * e;	// extended precision
			} f;

			void * v;
		} p;
	};
} primitive_t;


#endif
