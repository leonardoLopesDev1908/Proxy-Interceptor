#include "ProxyLinux.hpp"

ProxyLinux::ProxyLinux(const std::string_view& host, int port)
    : m_host(host), m_port(port) 
{
    create();
}


int ProxyLinux::create()
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);    

    if(m_socket != 0)
    {
        printf("[Error] socket\n");
        return 1;
    }

    return 0;
}

void ProxyLinux::start()
{
    if(create() == 1)
    {
        //throw error
        return;
    }
    
    struct addrinfo hints, *result = nullptr;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if(getaddrinfo(m_host, m_port, &hints, &result)
            != 0){
        std::cout << "Erro no getaddrinfo" << std::endl;
        close(serverSocket);
        return 1;
    }

    if(bind(serverSocket, result->ai_addr,
            (int) result->ai_addrlen)){
        std::cout << "Erro no bind" << std::endl;
        close(serverSocket);
        return 1;
    }

    listen(serverSocket, 5);

    int clientSocket = accept(serverSocket, result->ai_addr, (int)result->ai_addrlen);

    char buffer[1024] = { 0 };
    std::string response;

    ConnectionHandler newConn(clientSocket); 

    //Como criar o connectionHandler? Dar clientSocket pra ele apenas? Dar addrinfo?
}
