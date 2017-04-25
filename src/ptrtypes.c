#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <debug.h>
#include <ptrtypes.h>
#include <util.h>			// valloc()



smart_ptr_t * smart_ptr_ref(smart_ptr_t * ptr) {
	assert(ptr != NULL);
	assert(ptr->data != NULL);

	ptr->refcount++;
	return ptr;
}


int smart_ptr_unref(smart_ptr_t * ptr) {
	assert(ptr != NULL);
	assert(ptr->data != NULL);
	assert(ptr->refcount > 0);

	ptr->refcount--;

	if(ptr->refcount == 0) {
		if(ptr->dtor != NULL)
			ptr->dtor(ptr->data);

		free(ptr);
		return 1;
	}

	return 0;
}



smart_ptr_t * smart_alloc(size_t n) {
	smart_ptr_t * ptr;
	void * data;

	valloc((void **)&ptr, sizeof(smart_ptr_t), &data, n);

	ptr->data = data;
	ptr->refcount++;
	return ptr;
}
