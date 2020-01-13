#pragma once

#include "Queue.hpp"
#include "ApplicationLayer.hpp"

class Broker
{
    private:
    static const int PacketSize = sizeof(PacketStructure);
    char s_Buffer[PacketSize];


    
    public:
        Broker();
        void queueHandler();
        char* getUsers(char);
        int getUserConnection(char);
};