#define DataSize 1024

struct PacketStructure
{
    char PacketID;
    char ClientID;
    char Topic;
    char Data[DataSize]; 
};