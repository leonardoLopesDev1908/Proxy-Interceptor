#ifndef PROXY_WINDOWS_H
#define PROXY_WINDOWS_H

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>


class Proxy
{
	SOCKET m_socket;
	WSADATA wsaData;

	std::string& m_host;
	std::string m_port;

public:
	Proxy(std::string& host, std::string port);

	int create();
	void start();
};

#endif
