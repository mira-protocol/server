#include <stdio.h>
#include <mira_server/source.c>
#include <mira_server/server.h>

int main(void) {
	Server server = Server_Init(84);

	while (true) {
		Server_Update(&server);
	}
	return 0;
}
