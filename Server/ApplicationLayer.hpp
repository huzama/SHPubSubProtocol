#include "../PacketStructure.hpp"

class ApplicationLayer
{

    private:
    static const int PacketSize = sizeof(PacketStructure);
    char s_Buffer[PacketSize];
    char r_Buffer[PacketSize];
    int c_fd;
    char Topics[10];
    char User = 0;
    
    
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