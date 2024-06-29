#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "common.h"
#include "client.h"
#include "string.h"
#include "protocol.h"
#include "utils.h"

#define htonll(x) ((1 == htonl(1)) ? (x) : ((uint64_t) htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#define ntohll(x) ((1 == ntohl(1)) ? (x) : ((uint64_t) ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))

#define WORKER_EXIT do { \
	params->thread->completed = true; \
	free(params); \
	return NULL; \
} while (0)

void* ClientWorker(void* pparams) {
	puts("New client worker");
	ClientParams* params = (ClientParams*) pparams;

	time_t timer = time(NULL);

	while (true) {
		SetSocketBlocks(params->sock, false);

		uint8_t packetID;
		ssize_t size = recv(params->sock, &packetID, 1, MSG_WAITALL);

		if (size < 0) {
			if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
				goto ping;
			}
			else WORKER_EXIT;
		}

		SetSocketBlocks(params->sock, true);

		switch (packetID) {
			// GET packet
			case 'G': {
				GetRequest  req;
				GetResponse res = {
					.error    = ERROR_CODE_SUCCESS,
					.length   = 0,
					.contents = NULL
				};

				char ch    = 0;
				req.domain = String_New("");

				while (ch != '\n') {
					if (ch != 0) {
						String_AddChar(req.domain, ch);
					}

					size = recv(params->sock, &ch, 1, MSG_WAITALL);

					if (size < 0) WORKER_EXIT;
				}

				ch = 0;
				req.path = String_New("");

				while (ch != '\n') {
					if (ch != 0) {
						String_AddChar(req.path, ch);
					}

					size = recv(params->sock, &ch, 1, MSG_WAITALL);

					if (size < 0) WORKER_EXIT;
				}

				if (params->getFunc != NULL) {
					params->getFunc(&req, &res);
				}

				uint64_t length = res.length;
				res.length = htonll(res.length);

				if (send(params->sock, &res.error, sizeof(res.error), 0) < 0)   WORKER_EXIT;
				if (send(params->sock, &res.length, sizeof(res.length), 0) < 0) WORKER_EXIT;

				if (length > 0) {
					if (send(params->sock, res.contents, length, 0) < 0) WORKER_EXIT;
				}

				free(res.contents);
				break;
			}
			// PING packet
			case 'P': break;
			default: {
				fprintf(stderr, "Invalid packet ID '%.2X'\n", packetID);
				WORKER_EXIT;
			}
		}

		SetSocketBlocks(params->sock, false);

		ping:
		if (time(NULL) - timer > 0) {
			puts("sending ping packet");
			uint8_t pingPacket = 'P';
			if (send(params->sock, &pingPacket, 1, 0) < 0) WORKER_EXIT;
			timer = time(NULL);
		}
	}

	WORKER_EXIT;
}

#undef WORKER_EXIT
