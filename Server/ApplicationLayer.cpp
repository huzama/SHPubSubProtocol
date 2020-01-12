#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h> 
#include "ApplicationLayer.hpp"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>
#include <stdio.h>

extern int connCount;
int client_fd[100];
ApplicationLayer *clients[100];


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
    client_fd[connCount] = fd;
    clients[connCount] = this;
}


void ApplicationLayer::ClientHandling()
{
    PacketStructure *Packet = (PacketStructure*)r_Buffer;

    while(1)
    {
        if(recv(c_fd, r_Buffer, PacketSize, 0) <= 0)
        {
            perror("Reciving Failed");
            break;
        }
        else
        {   
            std::cout << "Data Recived from "<< Packet->ClientID << std::endl;
    

            switch(Packet->PacketID)
            {
                case 0:
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
    if (this->User)
        return;

    std::ifstream file("UserData/Users");
    std::string User, Password;

    while(getline(file, User, ':'))
    {
        getline(file , Password);
        
        if(User[0] == ClientID)
        {
            this->User = User[0]; 
            
            /*for(int i = 0, j = 0; i < Topic.size(); i++)
                if(Topic[i] != ' ')
                {
                        Topics[j] = Topic[i];
                        j++;
                }*/
            
            file.close();

            return;
        }
    }
}

void ApplicationLayer::topicSelection(char* DATA)
{
    std::cout<<"Topic Sele"<<std::endl;

}

void ApplicationLayer::updateFile(char Topic, char* Data)
{
    std::string File = "UserData/";
    File = File + Topic; 

    auto timeStamp = std::chrono::system_clock::now();
    
    std::fstream file;

    file.open(File.c_str(), std::ios::app);
    
    //  Sync Here
    file << Data + '\n';
    
    file.close();
}

char ApplicationLayer::getUser()
{
    return User;
}