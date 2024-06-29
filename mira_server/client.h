#ifndef MIRA_SERVER_CLIENT_H
#define MIRA_SERVER_CLIENT_H

#include <pthread.h>
#include "common.h"

typedef struct GetRequest GetRequest;
typedef struct GetResponse GetResponse;

typedef struct ClientThread ClientThread;
typedef struct ClientParams ClientParams;


struct ClientThread {
	pthread_t thread;
	bool      completed;
};

struct ClientParams {
	int           sock;
	ClientThread* thread;

	void (*getFunc)(GetRequest*, GetResponse*);
};

void* ClientWorker(void* pparams);

#endif
