#ifndef PROXY_WINDOWS_H
#define PROXY_WINDOWS_H

#define NOMINMAX

//NOLINTBEGIN(llvm-include-order)
#include <WinSock2.h>  
#include <ws2tcpip.h>   
#include <Windows.h>     
//NOLINTEND(llvm-include-order)

#include <iostream>
#include <string>


class ProxyWindows
{
	SOCKET m_socket = INVALID_SOCKET;
	WSADATA wsaData{};

	std::string m_host;
	std::string m_port;

public:
	ProxyWindows(std::string host, std::string port);
	~ProxyWindows();

	int create();
	int start();
	void stop();
};

#endif
