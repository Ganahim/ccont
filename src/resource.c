#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <debug.h>
#include <resource.h>


struct _RESOURCE_T * GRTBegin = NULL;
struct _RESOURCE_T * GRTEnd = NULL;
resource_handle_t GRTNextID = 1;				// Starting from one so that zero can be used as a special value
size_t GRTCapacity = 0;


int init_global_resource_table() {
	assert(GRTBegin == NULL);
	assert(GRTEnd == NULL);
	FUNC_DEBUG("");

	GRTCapacity = PAGESIZE;
	GRTBegin = malloc(GRTCapacity);
	GRTEnd = GRTBegin;

	return 0;
}


resource_handle_t resource_create(size_t len) {
	FUNC_DEBUG("");

	if(GRTNeedMore()) {
		GRTCapacity += PAGESIZE;
		GRTBegin = realloc(GRTBegin, GRTCapacity);

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
	assert((res-1) < GRTEntryCount());
	FUNC_DEBUG("");

	resource_t * p = (GRTBegin + (res - 1));
	assert(p->id == res);

	return p;
}


int resource_destroy(resource_handle_t res) {
	assert(res != 0);
}
