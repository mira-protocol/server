#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

Server Server_Init(uint16_t port) {
	Server ret;

	ret.sock       = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
	ret.clients    = NULL;
	ret.numClients = 0;
	ret.getFunc    = 0;

	if (ret.sock == -1) {
		perror("socket");
		exit(1);
	}

	if (setsockopt(
		ret.sock, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)
	) < 0) {
		perror("setsockopt");
		exit(1);
	}

	struct sockaddr_in addr;
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port        = htons(port);

	if (bind(ret.sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(1);
	}

	if (listen(ret.sock, 10) < 0) {
		perror("listen");
		exit(1);
	}

	printf("Listening on port %d\n", port);

	return ret;
}

void Server_Free(Server* server) {
	close(server->sock);
}

void Server_Update(Server* server) {
	struct sockaddr_in addr;

	int newSock = accept(
		server->sock, (struct sockaddr*) &addr, &(socklen_t) {sizeof(addr)}
	);

	if (newSock < 0) {
		if ((errno != EAGAIN) && (errno != EWOULDBLOCK)) {
			perror("accept");
			// should i exit?
		}
	}
	else {
		puts("new client");
		ClientParams* params = SafeMalloc(sizeof(ClientParams));

		server->clients = SafeRealloc(
			server->clients, (server->numClients + 1) * sizeof(ClientThread)
		);

		server->clients[server->numClients].completed = false;

		params->sock    = newSock;
		params->getFunc = server->getFunc;
		params->thread  = server->clients + server->numClients;

		pthread_create(
			&server->clients[server->numClients].thread, NULL, &ClientWorker, (void*) params
		);
	}
}
