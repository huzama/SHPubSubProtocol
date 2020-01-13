#include "ApplicationLayer.hpp"
#include <fstream>
#include "Broker.hpp"
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <sys/socket.h>
#include <iostream>


Node *updates;    
ApplicationLayer *users[26];
extern int serverStatus;

Broker::Broker()
{
    /*
    std::fstream topicUsers("Files/Topics");
    
    
    std::string f_Topic, f_User;

    while(getline(topicUsers, f_Topic, ':'))
    {
        getline(topicUsers , f_User);
        
        if(f_Topic[0] == Topic)
        {
            
            for(int i = 0, j = 0; i < f_User.size(); i++)
                if(f_User[i] != ' ')
                {
                        users[j] = f_User[i];
                        j++;
                }
            
            topicUsers.close();

            return;
        }
    }
    */



}



void Broker::queueHandler()
{
    char* userofTopic = 0;
    
    while(serverStatus)
    {
       while(updates && serverStatus)
        {
            userofTopic = getUsers(updates->Topic);
          
            if(!userofTopic)
                continue;

            for(int i = 0; i < 26; i++)
                getUserConnection(userofTopic[i]);

            updates = updates->Next;
        }


        sleep(0.5);
    }

}

char* Broker::getUsers(char Topic)
{
    char *users = new char[26]{ 0 };
    std::fstream topicUsers;
    topicUsers.open("UserData/Topics");

    std::string f_Topic, f_User;

    while(getline(topicUsers, f_Topic, ':'))
    {

        getline(topicUsers , f_User);
        
        if(f_Topic[0] == Topic)
        {
            std::cout << f_User << std::endl;

            for(int i = 0, j = 0; i < f_User.size(); i++)
                if(f_User[i] != ' ')
                {
                        users[j] = f_User[i];
                        j++;
                }
            
            topicUsers.close();

            return users;
        }
    }
    return 0;
}


int Broker::getUserConnection(char user) // Can be done by Dictionary
{
    for(int i = 0; i < 26; i++)
        if(users[i] && users[i]->getUser() == user)
        {
            char test[] = "Hor sunao Theek Thak oo";
            users[i]->sendPacket('2', user, '0', test);
        }
        
    return 0;
}