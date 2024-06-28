#ifndef MIRA_SERVER_SERVER_H
#define MIRA_SERVER_SERVER_H

#include "common.h"

typedef struct {
	int sock;
	ClientThread* clients;
	size_t        numClients;
} Server;

Server Server_Init(uint16_t port);
void   Server_Free(Server* server);
void   Server_Update(Server* server);

#endif
