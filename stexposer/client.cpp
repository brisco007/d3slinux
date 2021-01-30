//#include "client.h"
#include <iostream>
#include <string.h>

#include<sstream>
#include<string>
#include<boost/archive/binary_iarchive.hpp>
#include<boost/archive/binary_oarchive.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>


#include "state.h"
//#include "Networking.h"

using namespace std;
using std::string;
using std::cout;
using std::endl;

class Client{

    public:

   	Client(){

	    	client = socket(AF_INET, SOCK_STREAM, 0);

	    	if (client < 0){
			cout << "\nError establishing socket..." << endl;
			exit(1);
		}

		cout << "\n=> Socket client has been created..." << endl;


		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(portNum);
		inet_pton(AF_INET, ip, &server_addr.sin_addr);

		clientConnect();



	}


	void clientConnect(){
        	try{
            //connection
            //try to connect to the server on the port number
	    		if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0){
                    cout << "=> Connection to the server port number: " << portNum << endl;
                }else{
                    cout << "=> Error connecting to the server on port number : " << portNum << endl;
                }
		}
		catch(std::exception& e)
		{
		    std::cerr << e.what() << endl;
		}

    	}

    	//static void sendMessage(long id, char* state){

    	void sendMessage(long id,std::string state){
		try{
                oss.str(state);
		    // request/message from client
                state = oss.str();
               // send(client, oss.str(), bufsize, 0);
                send(client, state.c_str(), sizeof(state), 0);
		        	//send(client, (void*)id, sizeof(id), 0);

		}catch(std::exception& e){
		    std::cerr << e.what() << endl;
		}

    	}

    /*
    	void send_int(int myInt)
        {
         int my_net_id = htonl(myint);
         send(client, (const char*)&my_net_id, sizeof(my_net_id), 0);
        }


        void receive_int()
        {
         int client_id;
         auto bytesRead = read(connection, buffer, 100);

         std::cout << "The message was: " << buffer << std::endl;
         client_id = ntohl(buffer);
        }


        void send_long(long myLong)
        {
         int my_net_id = htonl(myLong);
         send(client, (const char*)&my_net_id, sizeof(my_net_id), 0);
        }

        void receive_long()
        {
         long client_id;
         auto bytesRead = read(connection, buffer, 100);

         std::cout << "The message was: " << buffer << std::endl;
         client_id = (long)ntohl(buffer);
        }


    	void sendState(State state){
              send_int(state.timestamp);
              send_long(state.nodeID);

    	}

    	void sendTuples(){

    	}
    */

   // static void recieveMessage(){
        // getting response from server
    //    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    //    if( error && error != boost::asio::error::eof ) {
    //        cout << "receive failed: " << error.message() << endl;
     //   }
    //    else {
      //      const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
      //      cout << data << endl;
       // }
     // }



    private:
	int client;
    	int portNum = 9999; // NOTE that the port number is same for both client and server
    	bool isExit = false;
    	int bufsize = 1024;
    	char buffer[1024];
    	char* ip = (char*)"127.0.0.1";
 	struct sockaddr_in server_addr;
 	long id = 11;
 	//std::string state = "the state value is test1";
 	std::istringstream oss;


};


int main() {
	long id = 11;
 	std::string state = "the state value is test1 slkdjfmlqsdf qsd flkqjsdmflf dqlksdfjqmsdlkfjqd qsdlkfjqsdlfkfjq dfqlksdfjfqmlsdkfjq dqsldffjkqdsjflqdsf qsdfdlkfjqdsmklffjqsdf qdslfkjqdslfkfqjsd fqmsdfq sdlkffjqdsfqlsjdfflqdk jqds fkqldsjfmqlkdfjfq sdfkqsdjfqlskdfjqsmdlfkjsdfsqkldsjff qlkdjfqmlkdsjf dfjqsldfjslkdjflqksdjfl sldkjflqksjdmldsfj sldkjflqskdfj sldkfjozeifj sldfjeozjf sdljozeifj qsdljzljeijf sdlkjozeifj sojief oisejfelj llkj";
	Client client1;
        client1.clientConnect();
    	client1.sendMessage(id,state);
    	client1.sendMessage(id,state);

    return 0;
}
