#ifndef MIRA_SERVER_CLIENT_H
#define MIRA_SERVER_CLIENT_H

#include <pthread.h>

typedef struct {
	pthread_t thread;
	bool      completed;
} ClientThread;

typedef struct {
	int           sock;
	ClientThread* thread;
} ClientParams;

void* ClientWorker(void* pparams);

#endif
