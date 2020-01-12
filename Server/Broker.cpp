#include "ApplicationLayer.hpp"
#include <fstream>
#include "Broker.hpp"

extern int client_fd;
extern ApplicationLayer *clients;

Broker::Broker(int topic)
    :Topic(topic)
{
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
}

