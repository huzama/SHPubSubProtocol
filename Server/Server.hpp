#pragma once


#include <netinet/ip.h>


class Server
{

private:
	int socketFD; 
	sockaddr_in serverAddr;
public:

    Server(int);
	int Connection();
	~Server();
};