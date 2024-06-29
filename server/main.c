#include <stdio.h>
#include <string.h>
#include <mira_server/protocol.h>
#include <mira_server/server.h>
#include <mira_server/client.h>
#include <mira_server/string.h>

void Get(GetRequest* req, GetResponse* res) {
	(void) req;

	const char* msg = "Hello, world!\n";

	res->error    = 0;
	res->contents = (uint8_t*) String_New(msg);
	res->length   = strlen(msg);
	puts("hello");
}

int main(void) {
	Server server  = Server_Init(25565);
	server.getFunc = &Get;

	while (true) {
		Server_Update(&server);
	}
	return 0;
}
