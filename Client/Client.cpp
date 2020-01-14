#include "Client.hpp"
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h> 
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include "../PacketStructure.hpp"

#define IP "192.168.43.181"

int Client::packetSize  = sizeof(PacketStructure);
int socketFD;

void* Client::RecivingPacket(void* arg)
{	char r_Buffer[Client::packetSize];
	pthread_t *thread_id = (pthread_t*)arg;
	PacketStructure *Packet = (PacketStructure*)r_Buffer;
		while(1)
	{
		if(recv(socketFD,r_Buffer,Client::packetSize,0)<=0)
		{
            perror("Reciving Failed");
            break;
        }
		 
		std::cout<<"message recieved: "<< Packet->Data <<std::endl;
	}  
	return NULL;
	
}

void Client::sendPacket(char PacktID, char ClientID, char Topic, char* DATA)
{    
    const int SizeofPacket = sizeof(PacketStructure);
    char Packet[SizeofPacket];
	
    PacketStructure *Modificaton = (PacketStructure*)Packet;

	Modificaton->PacketID = PacktID;
	Modificaton->ClientID = ClientID;
	Modificaton->Topic = Topic;

   if(DATA) 
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
	pthread_t thread_id;
    pthread_create(&thread_id, NULL, &Client::RecivingPacket, (void*)thread_id);
    SendCredentials();
}

void Client::SendCredentials()
{

   //char DATA[DataSize] = "check";
    sendPacket('0', GetUserID(),  '0', DATA);
	InputPacket();

}

void Client::InputPacket()
{
	std::cout<<"Enter Topic To Update"<<std::endl;
	std::cin>>topic;
    std::cout<<"enter updated data"<<std::endl;
	std::cin>>DATA;
	sendPacket('2', GetUserID(), topic,DATA );
}

void Client::CloseConnection()
{
	sendPacket('3', GetUserID(), '0',0 );
}

char Client::GetUserID()
{
 	std::fstream file;
    file.open("GetUserID");
    std::string User;
    getline(file, User, ':');
	char *Users = new char [User.length()+1];
	strcpy (Users, User.c_str());
	return *Users;
}

Client::~Client()
{
	sleep(15);
    close(socketFD);
}