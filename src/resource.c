#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <debug.h>
#include <resource.h>


struct _RESOURCE_T * GRTBegin = NULL;
struct _RESOURCE_T * GRTEnd = NULL;
struct _RESOURCE_T * GRTReuseEnd = NULL;
resource_handle_t GRTNextID = 1;				// Starting from one so that zero can be used as a special value
resource_handle_t GRTLastFreed = 0;
size_t GRTCapacity = 0;


int init_global_resource_table() {
	assert(GRTBegin == NULL);
	assert(GRTEnd == NULL);
	FUNC_DEBUG("");

	GRTCapacity = INITIAL_SIZE;
	GRTBegin = malloc(GRTCapacity);

	// Zero out null entry
	memset(GRTBegin, 0, sizeof(resource_t));

	// Point GRTEnd to the first valid entry
	GRTEnd = GRTBegin+1;

	return 0;
}


resource_handle_t resource_create(size_t len) {
	if(GRTNeedMore()) {
		// Save offset in case realloc invalidates GRTEnd
		size_t endOffset = GRTEntryCount();

		// Increase capacity in powers of two for efficiency
		GRTCapacity <<= 1;
		GRTBegin = realloc(GRTBegin, GRTCapacity);
		GRTEnd = GRTBegin + endOffset;

		FUNC_DEBUG("realloc %zu", GRTCapacity);
	}

	GRTEnd->id = GRTNextID++;
	GRTEnd->ref_count = 1;
	GRTEnd->data_len = len;
	GRTEnd->data = malloc(len);

	return (GRTEnd++)->id;
}

resource_t * resource_get(resource_handle_t res) {
	assert(res != 0);
	assert(res < GRTEntryCount());

	resource_t * p = (GRTBegin + res);
	assert(p->id == res);

	return p;
}

void * resource_get_data(resource_handle_t res) {
	assert(res != 0);
	return (GRTBegin + res)->data;
}


int resource_destroy(resource_handle_t res) {
	assert(res != 0);
	assert(res < GRTEntryCount());

	resource_t * p = resource_get(res);
	free(p->data);

	return 0;
}




void print_grt() {
	printf("GRT:\n");
	for(resource_t * p = GRTBegin+1; p != GRTEnd; p++) {
		if(p->ref_count)
			printf("\t%zu\n", p->id);
	}
}
