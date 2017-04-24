#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include <debug.h>

void msdelay(size_t n) {
	struct timespec t = {0, n * (1000 * 1000)};
	nanosleep(&t, NULL);
}




int main()
{

	return 0;
}
