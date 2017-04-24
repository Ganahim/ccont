#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <errno.h>
#include <fileutil.h>


long long file_size(const char * filename) {
	assert(filename != NULL);
	struct stat s;
	int e = stat(filename, &s);

	if(e != 0)
		return e;

	return s.st_size;
}
