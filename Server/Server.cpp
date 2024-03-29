#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Server.hpp"

#define IPaddress "192.168.43.181"

Server::Server(int PORT)
{
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socketFD == -1)
	{
		perror("\n Socket creation error \n"); 
	    exit(EXIT_FAILURE); 
	}
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, IPaddress, &serverAddr.sin_addr);
	memset(serverAddr.sin_zero, 0, sizeof serverAddr.sin_zero);		
	
	
	if(bind(socketFD, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("\n Binding Failed \n"); 
	    exit(EXIT_FAILURE); 
	}
	
	
	if (listen(socketFD, 100) < 0) 
	{ 
	    perror("Listning Failed"); 
	    exit(EXIT_FAILURE); 
	} 
}


int Server::Connection()
{
	int AddressSize = sizeof(serverAddr);
	int ConnectedFD = accept(socketFD, (sockaddr *)&serverAddr,(socklen_t*)&AddressSize);
	
	if (ConnectedFD < 0)
	{
		perror("Error in Accepting Connection"); 
    	exit(EXIT_FAILURE); 
	} 
	
	return ConnectedFD;
}

Server::~Server()
{
	close(socketFD);
}