#include "ProxyWindows.h"

Proxy::Proxy(std::string& host, std::string port)
	: m_host(host), m_port(port)
{
	create();
}

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
	}

	struct addrinfo* result = nullptr;
	struct addrinfo* ptr = nullptr;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(m_host.c_str(), m_port.c_str(), &hints, &result) != 0)
	{
		std::cout << "[Error] getaddrinfo\n";
		return;
	}

	m_socket = INVALID_SOCKET;
	m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "[Error] invalid socket\n";
		freeaddrinfo(result);
		return;
	}

}