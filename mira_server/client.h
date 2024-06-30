#ifndef MIRA_SERVER_CLIENT_H
#define MIRA_SERVER_CLIENT_H

#include <pthread.h>
#include "protocol.h"

struct ClientThread {
	pthread_t thread;
	bool      completed;
};
typedef struct ClientThread ClientThread;

typedef struct {
	int           sock;
	ClientThread* thread;

	void (*getFunc)(GetRequest*, GetResponse*);
} ClientParams;

void* ClientWorker(void* pparams);

#endif
