#include <thread>
#include <iostream>

#include "TCPSocket.h"
#include "TCPServer.h"

TCPServer::TCPServer(const char *ip, const char *port) {
	WSADATA wsaData;
	int e = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (e != 0) {
		std::cerr << "WSAStartup failed: " << e << std::endl;
	}

	struct addrinfo hints, *addrInfo = nullptr;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	e = getaddrinfo(ip, port, &hints, &addrInfo);
	if (e != 0) {
		std::cerr << "getaddrinfo failed: " << e << std::endl;
	}

	listenSocket = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);
	if (listenSocket == INVALID_SOCKET) {
		std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
	}

	e = bind(listenSocket, addrInfo->ai_addr, (int)addrInfo->ai_addrlen);
	if (e == SOCKET_ERROR) {
		std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
	}

	e = listen(listenSocket, SOMAXCONN);
	if (e == SOCKET_ERROR) {
		std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
	}

	freeaddrinfo(addrInfo);
}

TCPServer::~TCPServer() {
	closesocket(clientSocket);
	closesocket(listenSocket);

	WSACleanup();
}

void TCPServer::Run() {
	Running = true;

	while (Running) {
		clientSocket = accept(listenSocket, NULL, NULL);

		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
		}

		std::thread t(&TCPServer::Connect, this, clientSocket);
		t.detach();
	}
}

void TCPServer::Stop() {
	Running = false;
}

void TCPServer::Connect(SOCKET sock) {
	char buf[BUFSIZ];
	ZeroMemory(buf, sizeof(buf));

	while (recv(sock, buf, BUFSIZ, 0) > 0) {
		std::cout << buf << std::endl;
	}

	if (shutdown(sock, SD_SEND) == SOCKET_ERROR) {
		std::cerr << "shutdown failed: " << WSAGetLastError() << std::endl;
	}
}