#include <stdio.h>
#include "safe.h"

void* SafeMalloc(size_t size) {
	void* ret = malloc(size);

	if (ret == NULL) {
		perror("malloc");
		exit(1);
	}

	return ret;
}

void* SafeRealloc(const void* ptr, size_t size) {
	void* ret = realloc((void*) ptr, size);

	if (ret == NULL) {
		perror("realloc");
		exit(1);
	}

	return ret;
}
