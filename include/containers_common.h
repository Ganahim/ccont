#ifndef _CONTAINERS_COMMON_H
#define _CONTAINERS_COMMON_H

#ifndef NDEBUG
#	define ALLOC(...)			debug_alloc(__VA_ARGS__)
#	define REALLOC(...)		debug_realloc(__VA_ARGS__)
#	define FREE(...)			debug_free(__VA_ARGS__)
#endif

#ifndef ALLOC
#	define ALLOC(...)		malloc(__VA_ARGS__)
#endif
#ifndef REALLOC
#	define REALLOC(...)	realloc(__VA_ARGS__)
#endif
#ifndef FREE
#	define FREE(...)		free(__VA_ARGS__)
#endif


size_t compute_capacity(size_t size, size_t min);


#endif
