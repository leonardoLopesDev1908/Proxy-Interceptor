#include <iostream>
#include <stdlib.h>
#include <thread>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "Arguments missing. Execution example:\n";
		std::cout << "./Proxy 127.0.0.1 8080\n";
		return 1;
	}

	std::string host = argv[1];
	int port = atoi(argv[2]);

    //Resolve cross-platform to
    //choose what Proxy to launch
    //
    //std::thread proxyThread(proxy.create())
    
    //Launch concurrent proxy at endpoint
    //Main thread runs App and waits for user input
    /*
     * User main options:
     *  Show Queue of messages
     *  Chose message
     *  End app
    */

    /* User message options:
     *  Show request/response
     *  Edit request/response
     *  Forward
    */

	return 0;
}
