#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <w2tcpip.h>
#include <string>

class Proxy
{
	SOCKET m_socket;
	WSADATA wsaData;

	std::string_view& m_host;
	int m_port;

public:
	Proxy(std::string_view& host, int port);

	int create();
	void start();
};
