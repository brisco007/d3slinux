#include "Networking.h"
#include <iostream>



Networking::Networking()
{
    //ctor
}


static void clientConnect(){

    this.socket().async_connect(this.ep, connect_handler);
    this.service.run();

    void connect_handler(const boost::system::error_code & ec) {
        switch( errcode.value() ) {
            case boost::system::errc::success: {
                this.connected = true;// fine
            }
            break;

            case boost::system::errc::operation_canceled: {
                cout << "the operation was canceled " << endl; // operation cancelled
            }break;
            default: {
                cout << "something went wrong" << endl; // Assert unexpected case
            }

            break;
        }
    }
}

void serverAcc(){  // this method can be included in the receiver class as a static method

    typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
    io_service serviceS;
    ip::tcp::endpoint ep( ip::tcp::v4(), 8001)); // the server listen on port 8001
    ip::tcp::acceptor acc(service, ep);
    while ( true) {
        socket_ptr sock(new ip::tcp::socket(service));
        acc.accept(*sock);
        boost::thread( boost::bind(client_session, sock));

    }

    void client_session(socket_ptr sock) {
        while ( true) {
            char data[512]; // here we will store data
            size_t len = sock->read_some(buffer(data));
            if ( len > 0)
                write(*sock, buffer("ok received", 11));
        }
    }
}

static void sendMessage(){ // we will specify the arguments here
    if(this.connected == true){
        // here we send data
    }else{
        clientConnect();
        // here we send data after connecting to the server

    }
}

static void recieveMessages(){
    //here we reciere the data using the socket of the server
}


