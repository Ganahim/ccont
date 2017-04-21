#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <containers_common.h>




size_t compute_capacity(size_t size, size_t min) {
	size_t n = (min > 0 ? min : 1);
	while(n <= size) {
		n <<= 1;
	}

	return n;
}
