#include "ProxyLinux.hpp"

ProxyLinux::ProxyLinux(const std::string_view& host, int port)
    : m_host(host), m_port(port) {}


void ProxyLinux::start()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

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

    int clientSocket = accept(serverSocket, nullptr, nullptr);

    char buffer[1024] = { 0 };
    std::string response;
    
    while(buffer != "0"){
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::cout << "Message from client: " << buffer
            << std::endl;
        std::cout << "Response: ";
        std::getline(std::cin, response);
        send(clientSocket, response.data(), response.size(), 0);
    }

    close(serverSocket);
    m_socket = socket(AF_INET, SOCK_STREAM, 0);

}
