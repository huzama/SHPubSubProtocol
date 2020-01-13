#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h> 
#include "ApplicationLayer.hpp"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "Broker.hpp"
#include <string.h>
#include <chrono>
#include <stdio.h>

extern int connCount;
extern bool serverStatus;


extern Node *updates;    
extern ApplicationLayer *users[26];



void ApplicationLayer::sendPacket(char PacketID, char ClientID, char Topic, char* Data)
{
    static PacketStructure *Packet = (PacketStructure*)s_Buffer;
    Packet->PacketID = PacketID;
    Packet->ClientID = ClientID;
    Packet->Topic = Topic;
    if(Data)
        memcpy(Packet->Data,Data, DataSize);

    send(c_fd, Packet, PacketSize, 0);
}


ApplicationLayer::ApplicationLayer(int fd)
    :c_fd(fd)
{
}


void ApplicationLayer::ClientHandling()
{
    PacketStructure *Packet = (PacketStructure*)r_Buffer;

    while(serverStatus && User)
    {
        if(recv(c_fd, r_Buffer, PacketSize, 0) <= 0)
        {
            perror("Reciving Failed");
            break;
        }
        else
        {   
            switch(Packet->PacketID)
            {
                case '0':
                    Auth(Packet->ClientID);
                    break;
                case '1':
                    topicSelection(Packet->Data);
                    break;
                case '2':
                    updateFile(Packet->Topic, Packet->Data);
                    break;
                case '3':
                    goto end; 
                    break;

                default:
                    break;
            }
        }
    }
end:
    return;
}   


ApplicationLayer::~ApplicationLayer()
{
    close(c_fd);
    connCount--;
    std::cout<< "Client Disconnected!"<<std::endl;
}

void ApplicationLayer::Auth(char ClientID)
{
    if (this->User != 1)
        return;

    std::fstream file;
    file.open("UserData/Users");
    std::string User, Password;

    while(getline(file, User, ':'))
    {
        getline(file , Password);
        
        if(User[0] == ClientID)
        {
            std::cout << "Data Recived from "<< ClientID << std::endl;
            this->User = User[0]; 
            
            users[0] = this;

            file.close();

            return;
        }
    }
    this->User = 0;
}

void ApplicationLayer::topicSelection(char* DATA)
{
    std::cout<<"Topic Sele"<<std::endl;

}

void ApplicationLayer::updateFile(char Topic, char* Data)
{
    auto timeStamp = std::chrono::system_clock::now();

    std::string Path = "UserData/";
    Path = Path + Topic; 
    std::fstream file;
    file.open(Path.c_str(), std::ios::app);

    //  Sync Here
    file << Data + '\n';
    Node * temp = new Node;
    temp->Topic = Topic;
    updates = temp;
    file.close();
}

char ApplicationLayer::getUser()
{
    return User;
}