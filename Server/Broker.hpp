#pragma once

#include "ApplicationLayer.hpp"
#include "Queue.hpp"

class Broker
{
    private:
    static const int PacketSize = sizeof(PacketStructure);
    char s_Buffer[PacketSize];

    public:
        Broker();
        void queueHandler();
        char* getUsers(char);
        ApplicationLayer* getUserConnection(char);
        char* getUpdate(char Topic);

};