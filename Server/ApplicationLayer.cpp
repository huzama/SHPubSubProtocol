#include <sys/socket.h>
#include <sys/types.h>
#include "ApplicationLayer.hpp"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "Broker.hpp"
#include <string.h>
#include <chrono>
#include <stdio.h>

extern int ConnectedUsers;
extern bool serverStatus;
extern Node *updateQueue;    
extern ApplicationLayer *userObjects[26];

pthread_mutex_t ApplicationLayer::objectLock;


void ApplicationLayer::sendPacket(char PacketID, char ClientID, char Topic, char* Data)
{
    static PacketStructure *Packet = (PacketStructure*)s_Buffer;
    Packet->PacketID = PacketID;
    Packet->ClientID = ClientID;
    Packet->Topic = Topic;
    if(Data)
        memcpy(Packet->Data,Data, DataSize);

    send(userConnection, Packet, PacketSize, 0);
}


ApplicationLayer::ApplicationLayer(int fd)
    :userConnection(fd)
{
    if(pthread_mutex_init(&objectLock, NULL) != 0)
        std::cout << "Object Mutex init Failed" << std::endl;
}


void ApplicationLayer::ClientHandling()
{
    PacketStructure *Packet = (PacketStructure*)r_Buffer;

    while(serverStatus && userID != -1)
    {
        if(recv(userConnection, r_Buffer, PacketSize, 0) <= 0)
        {
            perror("Reciving Failed");
            break;
        }
        else
        {   
            std::cout << r_Buffer << std::endl;
            switch(Packet->PacketID)
            {
                case '0':
                    Auth(Packet->ClientID);
                    break;
                case '1':
                    topicSelection(Packet->Data);
                    break;
                case '2':
                    saveUpdate(Packet->Topic, Packet->Data);
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
    pthread_mutex_destroy(&objectLock);
    close(userConnection);
    ConnectedUsers--;
    std::cout << "Client Disconnected!"<<std::endl;
}

void ApplicationLayer::Auth(char ClientID)
{
    if (this->userID)
        return;

    std::fstream file;
    file.open("UserData/Users");
    std::string User, Password;

    while(getline(file, User, ':'))
    {
        getline(file , Password);
        
        if(User[0] == ClientID)
        {
            static int connectedClients = 0;
            std::cout << "Connection Established with: "<< ClientID << std::endl;
            this->userID = ClientID; 
            
            
            // Saving this pointer of clients in a Global Array
            pthread_mutex_lock(&objectLock);
            userObjects[connectedClients] = this;
            connectedClients++;
            pthread_mutex_unlock(&objectLock);


            file.close();
            return;
        }
    }

    this->userID = -1;
}


void ApplicationLayer::topicSelection(char* DATA)
{
    std::cout<<"Topic Sele"<<std::endl;

}

void ApplicationLayer::saveUpdate(char Topic, char* Data)
{
    /*std::string Path = "UserData/";
    Path = Path + Topic; 
    std::fstream file;
    file.open(Path.c_str(), std::ios::app);
    file << Data + '\n';
*/
    Node *temp = new Node;
    temp->Topic = Topic;

    memcpy(temp->Data, Data, DataSize);
    
    addInQueue(updateQueue, temp);

    //file.close();
}

char ApplicationLayer::getUser()
{
    return userID;
}