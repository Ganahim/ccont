#ifndef _RESOURCE_H
#define _RESOURCE_H

#include <stddef.h>



typedef size_t resource_handle_t;
struct _RESOURCE_T;


/* Pointer to the null entry */
extern struct _RESOURCE_T * GRTBegin;

/* Pointer to the past-end entry */
extern struct _RESOURCE_T * GRTEnd;

/* The next ID to be assigned */
extern resource_handle_t GRTNextID;

/* The ID of the most recently freed entry */
extern resource_handle_t GRTLastFreed;

/* Number of bytes currently reserved for GRT */
extern size_t GRTCapacity;

/* Page size */
#define INITIAL_SIZE 4096

/* Number of entries currently in use */
#define GRTEntryCount()		(GRTEnd - GRTBegin)

/* Number of bytes currently in use */
#define GRTSize()				(GRTEntryCount() * sizeof(struct _RESOURCE_T))


/* Number of unused bytes */
#define GRTUnused()			(GRTCapacity - GRTSize())

/* Return nonzero if reallocation is needed in order to add a new entry */
#define GRTNeedMore()		(GRTUnused() < sizeof(struct _RESOURCE_T))

/* Return nonzero if reallocation to a smaller size is desirable */
#define GRTNeedLess()		(GRTUnused() >= INITIAL_SIZE)



#define DEBUG_RESOURCE(P)	fprintf(stderr, "id: %zu\nref_count: %zu\ndata_len: %zu\n\n", (P)->id, (P)->ref_count, (P)->data_len)

typedef struct _RESOURCE_T {
	resource_handle_t id;
	size_t ref_count;
	size_t data_len;
	void * data;
} resource_t;



int init_global_resource_table();


resource_handle_t resource_create(size_t len);
resource_t * resource_get(resource_handle_t res);
void * resource_get_data(resource_handle_t res);

int resource_destroy(resource_handle_t res);


void print_grt();
void print_reuse_stack();
#endif
