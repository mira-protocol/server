#ifndef MIRA_SERVER_PROTOCOL_H
#define MIRA_SERVER_PROTOCOL_H

#include "common.h"

enum {
	ERROR_CODE_SUCCESS        = 0,
	ERROR_CODE_PAGE_NOT_FOUND = 1,
	ERROR_CODE_BAD_PATH       = 2,
	ERROR_CODE_UNKNOWN_DOMAIN = 3
};

typedef struct {
	const char* domain;
	const char* path;
} GetRequest;

typedef struct {
	uint8_t  error;
	uint64_t length;
	uint8_t* contents;
} GetResponse;

#endif
