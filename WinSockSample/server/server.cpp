#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#include "TCPSocket.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

int main() {
	TCPSocket *tcp = new TCPSocket();

	SOCKET listenSocket = INVALID_SOCKET;
	SOCKET clientSocket = INVALID_SOCKET;

	if (!tcp->initSocket(DEFAULT_IP, DEFAULT_PORT)) {
		return 1;
	}

	if (!tcp->createSocket(listenSocket)) {
		return 1;
	}

	if (!tcp->bindSocket(listenSocket)) {
		return 1;
	}

	if (!tcp->listenSocket(listenSocket)) {
		return 1;
	}

	char recvbuf[DEFAULT_BUFLEN];
	memset(recvbuf, '\0', DEFAULT_BUFLEN);
	while (tcp->acceptSocket(listenSocket, clientSocket)) {
		int recvlen;
		int sendlen;
		do {
			recvlen = tcp->recvSocket(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);

			if (recvlen > 0) {
				std::cout << recvbuf << std::endl;
				sendlen = tcp->sendSocket(clientSocket, recvbuf, recvlen, 0);
			}
		} while (recvlen > 0);
	}

	if (!tcp->shutdownSocket(clientSocket, SD_SEND))
		return 1;

	tcp->closeSocket(clientSocket);

	return 0;
}
