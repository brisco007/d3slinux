#ifndef NETWORKING_H
#define NETWORKING_H
#include <boost/array.hpp>
#include <boost/asio.hpp>
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

    io_service service;
    socket_ptr socket(service);
    ip::tcp::endpoint ep( ip::address::from_string("192.168.1.10"), 8001)); // the server listen on port 8001
    ip::tcp::acceptor acc(service, ep);
};

#endif // NETWORKING_H
