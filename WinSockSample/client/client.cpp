#include <iostream>

#include "TCPSocket.h"
#include "TCPClient.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "27015"

int main() {
	TCPClient *client = new TCPClient(DEFAULT_IP, DEFAULT_PORT);

	client->Run();

	while (client->isRunning()) {
		client->Write("Test message.\n");

		Sleep(2000);
	}

	return 0;
}
