#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Proxy
{
    int m_socket;
    std::string_view& m_host;
    int m_port;

public:
    
    Proxy(std::string_view& host, int port);    
    Proxy(const Proxy& copy) = delete;
    Proxy(Proxy&& move) = delete;

    void start();

};
