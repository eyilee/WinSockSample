#include <iostream>

#include "TCPSocket.h"
#include "TCPClient.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "27015"

int main() {
	TCPClient *client = new TCPClient(DEFAULT_IP, DEFAULT_PORT);

	const char *sendbuf = "this is a test\n\0";
	client->Write(sendbuf);

	//// Receive data until the server closes the connection
	//do {
	//	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	//	if (iResult > 0)
	//		printf("Bytes received: %d\n", iResult);
	//	else if (iResult == 0)
	//		printf("Connection closed\n");
	//	else
	//		printf("recv failed: %d\n", WSAGetLastError());
	//} while (iResult > 0);

	//// shutdown the send half of the connection since no more data will be sent
	//iResult = shutdown(ConnectSocket, SD_SEND);
	//if (iResult == SOCKET_ERROR) {
	//	printf("shutdown failed: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	WSACleanup();
	//	return 1;
	//}

	//// cleanup
	//closesocket(ConnectSocket);
	//WSACleanup();

	return 0;
}
