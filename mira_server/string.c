#include <string.h>
#include "safe.h"
#include "string.h"

char* String_New(const char* src) {
	char* ret = SafeMalloc(strlen(src) + 1);
	strcpy(ret, src);
	return ret;
}

char* String_AddChar(const char* str, char ch) {
	char* ret = SafeRealloc(str, strlen(str) + 2);
	strcpy(ret, str);
	strncat(ret, &ch, 1);
	return ret;
}
