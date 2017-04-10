#ifndef _DEBUG_H
#define _DEBUG_H

#ifndef NDEBUG
#	include <stdio.h>
#	define FUNC_DEBUG(...)	fprintf(stderr, ">> %s():", __func__); fprintf(stderr, " "__VA_ARGS__); fputc('\n', stderr);
#endif


#endif
