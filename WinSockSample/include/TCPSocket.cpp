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

TCPSocket::TCPSocket() :addrInfo(nullptr) {
}

TCPSocket::~TCPSocket() {
	freeaddrinfo(addrInfo);
	WSACleanup();
}

bool TCPSocket::initSocket(const char *ip, const char *port) {
	int e = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (e != 0) {
		printf("initSocket(): WSAStartup failed: %d\n", e);
		return false;
	}

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	e = getaddrinfo(ip, port, &hints, &addrInfo);
	if (e != 0) {
		printf("initSocket(): getaddrinfo failed: %d\n", e);
		return false;
	}

	return true;
}

bool TCPSocket::createSocket(SOCKET &sock) {
	sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);
	if (sock == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		return false;
	}

	return true;
}

bool TCPSocket::bindSocket(SOCKET &sock) {
	int e = bind(sock, addrInfo->ai_addr, (int)addrInfo->ai_addrlen);
	if (e == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		return false;
	}

	return true;
}

bool TCPSocket::listenSocket(SOCKET &sock) {
	int e = listen(sock, SOMAXCONN);
	if (e == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		return false;
	}

	return true;
}

bool TCPSocket::acceptSocket(SOCKET &listenSock, SOCKET &clientSock)
{
	clientSock = accept(listenSock, NULL, NULL);
	if (clientSock == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		return false;
	}

	return true;
}

bool TCPSocket::shutdownSocket(SOCKET &sock, int how)
{
	int e = shutdown(sock, how);
	if (e == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		return false;
	}

	return true;
}

void TCPSocket::closeSocket(SOCKET &sock) {
	closesocket(sock);
}

int TCPSocket::recvSocket(SOCKET &sock, char *buf, int len, int flags) {
	int e = recv(sock, buf, len, flags);
	if (e == SOCKET_ERROR) {
		printf("recv failed: %d\n", WSAGetLastError());
	}

	return e;
}

int TCPSocket::sendSocket(SOCKET &sock, char *buf, int len, int flags) {
	int e = send(sock, buf, len, flags);
	if (e == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
	}

	return e;
}
