#define DataSize 100

struct PacketStructure
{
    char PacketID;
    char ClientID;
    char Topic;
    char Data[DataSize]; 
};