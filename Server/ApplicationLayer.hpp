#pragma once

#include <pthread.h> 
#include "../PacketStructure.hpp"

class ApplicationLayer
{
    private:
        static const int PacketSize = sizeof(PacketStructure);
    
    public:
        static pthread_mutex_t objectLock;

    private:
        char s_Buffer[PacketSize];
        char r_Buffer[PacketSize];
        int userConnection;
        char userID;
    
    public:
        ApplicationLayer(int fd);
        void ClientHandling();
        void sendPacket(char, char, char, char*);
        
        char getUser();
        void Auth(char);
        void topicSelection(char*);
        void updateFile(char, char*);

        ~ApplicationLayer();
};

void* Publish(void*);        