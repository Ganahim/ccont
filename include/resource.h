#ifndef _RESOURCE_H
#define _RESOURCE_H

#include <stddef.h>



typedef size_t resource_handle_t;
struct _RESOURCE_T;


extern struct _RESOURCE_T * GRTBegin;
extern struct _RESOURCE_T * GRTEnd;
extern resource_handle_t GRTNextID;

/* Number of bytes currently reserved for GRT */
extern size_t GRTCapacity;

/* Page size */
#define PAGESIZE 4096

/* Number of entries currently in use */
#define GRTEntryCount()		(GRTEnd - GRTBegin)

/* Number of bytes currently in use */
#define GRTSize()				(GRTEntryCount() * sizeof(struct _RESOURCE_T))


/* Number of unused bytes */
#define GRTUnused()			(GRTCapacity - GRTSize())

/* Return nonzero if reallocation is needed in order to add a new entry */
#define GRTNeedMore()		(GRTUnused() < sizeof(struct _RESOURCE_T))

/* Return nonzero if reallocation to a smaller size is desirable */
#define GRTNeedLess()		(GRTUnused() >= PAGESIZE)



typedef struct _RESOURCE_T {
	resource_handle_t id;
	size_t ref_count;
	size_t data_len;
	void * data;
} resource_t;



int init_global_resource_table();


resource_handle_t resource_create(size_t len);
resource_t * resource_get(resource_handle_t res);

int resource_destroy(resource_handle_t res);


#endif
