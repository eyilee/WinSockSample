#pragma once

class TCPSocket {
public:

private:
	WSADATA wsaData;
	struct addrinfo *addrInfo;

public:
	TCPSocket();
	~TCPSocket();
	bool initSocket(const char *ip, const char *port);
	bool createSocket(SOCKET &sock);
	bool bindSocket(SOCKET &sock);
	bool listenSocket(SOCKET &sock);
	bool acceptSocket(SOCKET &listenSock, SOCKET &clientSock);
	int recvSocket(SOCKET &sock, char *buf, int len, int flags);
	int sendSocket(SOCKET &sock, char *buf, int len, int flags);
	bool shutdownSocket(SOCKET &sock, int how);
	void closeSocket(SOCKET &sock);

private:
};
