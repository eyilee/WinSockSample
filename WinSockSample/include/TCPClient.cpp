#include <thread>
#include <iostream>

#include "TCPSocket.h"
#include "TCPClient.h"

TCPClient::TCPClient(const char * ip, const char * port) {
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

	connectSocket = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);
	if (connectSocket == INVALID_SOCKET) {
		std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
	}

	e = connect(connectSocket, addrInfo->ai_addr, (int)addrInfo->ai_addrlen);
	if (e == SOCKET_ERROR) {
		std::cerr << "connect failed: " << WSAGetLastError() << std::endl;
	}

	freeaddrinfo(addrInfo);
}

TCPClient::~TCPClient() {
	closesocket(connectSocket);

	WSACleanup();
}

void TCPClient::Run() {
	if (Running) {
		return;
	}

	Running = true;

	std::thread t(&TCPClient::Connect, this, connectSocket);
	t.detach();
}

void TCPClient::Stop() {
	Running = false;
}

void TCPClient::Connect(SOCKET sock) {
	char buf[BUFSIZ];
	ZeroMemory(buf, sizeof(buf));

	while (recv(sock, buf, BUFSIZ, 0) > 0) {
		std::cout << buf;
	}

	if (shutdown(sock, SD_SEND) == SOCKET_ERROR) {
		std::cerr << "shutdown failed: " << WSAGetLastError() << std::endl;
	}
}

void TCPClient::Write(const char *data) {
	int e = send(connectSocket, data, (int)strlen(data), 0);
	if (e == SOCKET_ERROR) {
		std::cerr << "send failed: " << WSAGetLastError() << std::endl;
	}
}
