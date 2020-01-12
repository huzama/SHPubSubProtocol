class Client
{
    private:

        int socketFD; 
        void sendPacket(char, char, char, char*);

    public:
        Client(int);
        void SendCredentials();
        char GetUserID();
        ~Client();
};