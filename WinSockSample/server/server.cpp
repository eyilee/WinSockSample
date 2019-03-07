#include <iostream>

#include "TCPSocket.h"
#include "TCPServer.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "27015"

int main() {
	TCPServer *server = new TCPServer(DEFAULT_IP, DEFAULT_PORT);

	server->Run();

	return 0;
}
