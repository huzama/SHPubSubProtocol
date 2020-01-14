#include "Broker.hpp"
#include "Server.hpp"
#include "ApplicationLayer.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>

extern ApplicationLayer *userObjects[26];
int ConnectedUsers = 2;
bool serverStatus = 1;

void* connHandle(void *c_FD)
{
    ConnectedUsers++;

    std::cout << "Client "<< ConnectedUsers <<" connected!"<<std::endl;
    
    ApplicationLayer connection(*(int*)c_FD);
    
    connection.ClientHandling();
    
    return 0;
}

void* clientDispatcher(void* arg)
{
    Server myServer(5656);

    pthread_t *thread_id = (pthread_t*)arg;


    std::cout << "Waiting for incoming Connections..." << std::endl;
    
    while(serverStatus)
    {
        int ClientConn = myServer.Connection();
        pthread_create(&thread_id[ConnectedUsers], NULL, connHandle, (void*)&ClientConn);
    }

    return 0;
}

void* Topics(void* arg)
{
    pthread_t *thread_id = (pthread_t*)arg;

    Broker publisher;
    publisher.queueHandler();

    return 0;
}



int main(int argc, char *argv[])
{
    pthread_t thread_id[100];


    pthread_create(&thread_id[0], NULL, clientDispatcher, (void*)thread_id);
    pthread_create(&thread_id[1], NULL, Topics, (void*)thread_id);
    
    std::cin >> serverStatus;
    
    for(int i = 0; i < 26; i++)
        if(userObjects[i])
            userObjects[i]->deleteObject();

    std::cout << ConnectedUsers <<std::endl;

    sleep(1);
    return 0;
}