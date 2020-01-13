#include "Broker.hpp"
#include "Server.hpp"
#include "ApplicationLayer.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>


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

void* Dispatcher(void* arg)
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
    Broker publisher;
    publisher.queueHandler();

    return 0;
}



int main(int argc, char *argv[])
{
    pthread_t thread_id[100];


    pthread_create(&thread_id[0], NULL, Dispatcher, (void*)&thread_id);
    pthread_create(&thread_id[1], NULL, Topics, (void*)&thread_id);
    
    std::cin >> serverStatus;
    sleep(2);

    return 0;
}