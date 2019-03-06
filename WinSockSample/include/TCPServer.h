#pragma once

class TCPServer {
private:
	SOCKET listenSocket = INVALID_SOCKET;
	SOCKET clientSocket = INVALID_SOCKET;

public:
	TCPServer(const char *ip, const char *port);
	~TCPServer();

	void Run();
	void Stop();
	void Connect(SOCKET sock);
	/*void Read();
	void Write();

	virtual void OnRead();
	virtual void OnWrite();*/

private:
	bool Running = false;
};
