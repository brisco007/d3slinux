#ifndef NETWORKING_H
#define NETWORKING_H
#include "state.h"


class Networking
{

    public:
        using boost::asio;
        typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

        Networking();

        clientConnect();

        void serverAcc()

        static void sendMessage(long nodeID, State state); // I remode the ip address as we send at a particular address

        static void recieveMessages();


    protected:

    private:

    string ipReceiver = "192.168.1.10"; // this address has to be changed and specified
    bool connected = false;
};

#endif // NETWORKING_H
