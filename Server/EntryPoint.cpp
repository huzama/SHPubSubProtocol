#include "Server.hpp"
#include "ApplicationLayer.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Publisher.hpp"


int connCount = 2;
bool serverStatus = 1;

void* connHandle(void *c_FD)
{
    connCount++;

    int *Client = (int*)c_FD;
    std::cout << "Client "<< connCount <<" connected!"<<std::endl;
    
    ApplicationLayer connection(*Client);
    
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
        pthread_create(&thread_id[connCount], NULL, connHandle, (void*)&ClientConn);
    }

    return 0;
}

void* Publish(void* arg)
{
    Broker filePublishing(*(int*)arg);



    /*int TopicNo = *(int*)arg;    
    
    std::string File = "UserData/";
    File = File + std::to_string(TopicNo);

    std::ifstream file;
    
    

    file.open(File.c_str());

    file.close();
*/
    return 0;
}

void* Topics(void* arg)
{
    pthread_t thread_id;
    for(int i = 0; i < 10; i++)
    {
        pthread_create(&thread_id, NULL, Publish, (void*)&i);
    }
    return 0;
}


int main(int argc, char *argv[])
{
    pthread_t thread_id[100];

    pthread_create(&thread_id[0], NULL, Dispatcher, (void*)&thread_id);
    pthread_create(&thread_id[1], NULL, Topics, (void*)&thread_id);
    
    std::cin >> serverStatus;

    return 0;
}