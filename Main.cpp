#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "Arguments missing. Execution example:\n";
		std::cout << "./Proxy 127.0.0.1 8080\n";
		return 1;
	}

	std::string host = argv[1];
	int port = atoi(argv[2]);


	return 0;
}