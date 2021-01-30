//#include "client.h"
#include <iostream>
#include <string.h>

#include<string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include <list>
#include "state.h"
#include "g_stagestypes.h"
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
		
		
		state.nodeID = 1611;
		state.timestamp = 11234;
		V0::Tuple tuple1(1,"lskjdf",(double)343);
		Tuple tuple2(1,"lskjdf",(double)793);
		Tuple tuple3(1,"lskjdf",(double)643);
		
		state.list_of_tuples.push_back(tuple1);
		state.list_of_tuples.push_back(tuple2);
		state.list_of_tuples.push_back(tuple3);
		
		stateString = toStringState();

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

    	void sendMessage(){
		try{
		
		cout<< "sending this state: " << stateString.c_str() << endl;
		    // request/message from client
               // send(client, oss.str(), bufsize, 0);
                send(client, stateString.c_str(), sizeof(stateString.c_str()), 0);
		        	//send(client, (void*)id, sizeof(id), 0);

		}catch(std::exception& e){
		    std::cerr << e.what() << endl;
		}

    	}
    	
    	
    	void sendMessage(string stateString){
		try{
		
		cout<< "sending this state: " << stateString.c_str() << endl;
		    // request/message from client
               // send(client, oss.str(), bufsize, 0);
		
                send(client, stateString.c_str(), sizeof(stateString.c_str()), 0);
		        	//send(client, (void*)id, sizeof(id), 0);

		}catch(std::exception& e){
		    std::cerr << e.what() << endl;
		}

    	}
    	
    	
    	
    	string toStringState(){
    		string str ="";
    		 
    		std::list<Tuple> mylist = state.list_of_tuples;
  		std::list<Tuple>::iterator it;
    		str = str +"nodeId="+std::to_string(state.nodeID)+";tupleList=[";
    		for (it=mylist.begin(); it!=mylist.end(); ++it){
    			str = str + it->toString() +"," ;
    		}
    		str = str + "]";
    		
    		return str;
    	
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
 	State state;
 	string stateString;


};


int main() {
	
	Client client1;
        client1.clientConnect();
    	client1.sendMessage();

    return 0;
}
