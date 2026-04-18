#include "ProxyWindows.h"
#include "ConnectionHandler.h"

Proxy::Proxy(std::string_view& host, int port)
	: m_host(host), m_port(port) {}

int Proxy::create()
{
	int teste;

	teste = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (teste != 0)
	{
		std::cout << "[Error] start\n";
		return 1;
	}
	return 0;
}

void Proxy::start()
{
	if (create() != 0)
	{
		//throw std::err...
		return;
	}

	struct addrinfo* result = nullptr;
	struct addrinfo *ptr = nullptr;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	
	if (getaddrinfo(m_host, m_port, &hints, &result) != 0)
	{
		std::cout << "[Error] getaddrinfo\n";
		WSACleanup();
		return;
	}

	m_socket = INVALID_SOCKET;
	m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "[Error] invalid socket\n";
		freeaddrinfo(&result);
		WSACleanup();
		return;
	}

	if (bind(m_socket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
	{
		std::cout << "[Error] binding socket\n";
		freeaddrinfo(&result);
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	freeaddrinfo(&result);

	if (listen(m_socket, 5) == SOCKET_ERROR)
	{
		std::cout << "[Error] listening socket\n";
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	SOCKET client;
	if ((client = accept(client, NULL, NULL)) == INVALID_SOCKET)
	{
		std::cout << "[Error] accepting\n";
		closesocket(m_socket);
		WSACleanup();
		return;
	}
	
	ConnectionHandler newConn(client);

}
