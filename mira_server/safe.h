#ifndef MIRA_SERVER_SAFE_H
#define MIRA_SERVER_SAFE_H

#include "common.h"

void* SafeMalloc(size_t size);
void* SafeRealloc(const void* ptr, size_t size);

#endif
