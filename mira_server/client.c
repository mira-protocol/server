#include <stdio.h>
#include <sys/socket.h>
#include "common.h"
#include "client.h"
#include "string.h"

void* ClientWorker(void* pparams) {
	puts("New client worker");
	ClientParams* params = (ClientParams*) pparams;

	while (true) {
		char    ch;
		ssize_t size = recv(params->sock, &ch, 1, MSG_WAITALL);
		putchar(ch);
	}

	free(params);
	return NULL;
}
