#include "Client.hpp"
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h> 
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include "../PacketStructure.hpp"


#define IP "127.0.0.1"

void Client::sendPacket(char PacktID, char ClientID, char Topic, char* DATA)
{
    
    const int SizeofPacket = sizeof(PacketStructure);
    char Packet[SizeofPacket];
	
    PacketStructure *Modificaton = (PacketStructure*)Packet;

	Modificaton->PacketID = PacktID;
	Modificaton->ClientID = ClientID;
	Modificaton->Topic = Topic;

    memcpy(Modificaton->Data, DATA, DataSize);

    send(socketFD, Packet, SizeofPacket, 0);
}

Client::Client(int PORT)
{

	socketFD = socket(AF_INET,SOCK_STREAM,0);
	
	if(socketFD == -1)
	{
		perror("\n Socket creation error \n"); 
	    exit(EXIT_FAILURE); 
	}

	struct sockaddr_in s_addr;
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);
	inet_aton(IP,&s_addr.sin_addr);

	if(connect(socketFD, (struct sockaddr*)&s_addr, sizeof(s_addr)) < 0)
	{
		perror("\nConnection Failed \n"); 
	    exit(EXIT_FAILURE); 
	}

    SendCredentials();
}

void Client::SendCredentials()
{

    char DATA[DataSize] = "Tayyaba Pagal HA";
    sendPacket(0, GetUserID(),  '0', DATA);

}



char Client::GetUserID()
{
  return 'D';   
}

Client::~Client()
{
	sleep(1);
    close(socketFD);
}