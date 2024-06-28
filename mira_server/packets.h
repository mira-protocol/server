#ifndef MIRA_SERVER_PACKETS_H
#define MIRA_SERVER_PACKETS_H

#include "common.h"

enum {
	ERROR_CODE_SUCCESS        = 0,
	ERROR_CODE_PAGE_NOT_FOUND = 1,
	ERROR_CODE_BAD_PATH       = 2,
	ERROR_CODE_UNKNOWN_DOMAIN = 3
};

typedef struct {
	char* domain;
	char* path;
} Packet_Get;

typedef struct {
	uint8_t  errorCode;
	uint64_t length;
	uint8_t* contents;
} PacketRes_Get;

#endif
