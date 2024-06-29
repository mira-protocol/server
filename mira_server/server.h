#ifndef MIRA_SERVER_SERVER_H
#define MIRA_SERVER_SERVER_H

#include "common.h"

typedef struct ClientThread ClientThread;
typedef struct GetRequest GetRequest;
typedef struct GetResponse GetResponse;

typedef struct Server Server;

struct Server {
	int sock;
	ClientThread* clients;
	size_t        numClients;

	void (*getFunc)(GetRequest*, GetResponse*);
};

Server Server_Init(uint16_t port);
void   Server_Free(Server* server);
void   Server_Update(Server* server);

#endif
