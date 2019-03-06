#pragma once

class TCPClient {
private:
	SOCKET connectSocket = INVALID_SOCKET;

public:
	TCPClient(const char *ip, const char *port);
	~TCPClient();

	//void Run();
	//void Stop();
	//void Connect(SOCKET sock);
	//void Read();
	void Write(const char *data);

	//virtual void OnRead();
	//virtual void OnWrite();

private:
	bool Running = false;
};
