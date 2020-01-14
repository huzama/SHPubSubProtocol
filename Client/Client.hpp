#pragma once

#include <string.h> 
class Client
{
    public:
    static int packetSize;

    private:
        char topic; 
        void sendPacket(char, char, char, char*);
        char DATA[100];
       
    public:
        Client(int);
        void SendCredentials();
        void InputPacket();
        void CloseConnection();
        char GetUserID();
        static void* RecivingPacket(void*);
        ~Client();
};