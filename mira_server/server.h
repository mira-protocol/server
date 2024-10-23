#ifndef MIRA_SERVER_SERVER_H
#define MIRA_SERVER_SERVER_H

#include "common.h"
#include "protocol.h"

struct ClientThread;

typedef struct {
	int                  sock;
	struct ClientThread* clients;
	size_t               numClients;

	void (*getFunc)(GetRequest*, GetResponse*);
} Server;

Server Server_Init(uint16_t port);
void   Server_Free(Server* server);
void   Server_Update(Server* server);

#endif
