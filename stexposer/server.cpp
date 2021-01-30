//#include "server.h"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read

//#include "state.h"
//#include "Networking.h"

using namespace std;
using std::string;
using std::cout;
using std::endl;


class Server
{

	public:
    		//constructor for accepting connection from client

	      	Server(){
	      		sockaddr.sin_family = AF_INET;
			sockaddr.sin_addr.s_addr = INADDR_ANY;
			sockaddr.sin_port = htons(9999); // htons is necessary to convert a number to network byte order

	      		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	      		if (sockfd == -1) {
				std::cout << "Failed to create socket. errno: " << errno << std::endl;
				exit(EXIT_FAILURE);
			}

			//try to bind socket on port
			if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
				std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
			  	exit(EXIT_FAILURE);
			}

			// Start listening. Hold at most 10 connections in the queue
			if (listen(sockfd, 10) < 0) {
				std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
				exit(EXIT_FAILURE);
			}

			// Grab a connection from the queue
			auto addrlen = sizeof(sockaddr);
			connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
			if (connection < 0) {
				std::cout << "Failed to grab connection. errno: " << errno << std::endl;
				exit(EXIT_FAILURE);
			}




	      	}

	      	void receiveMessages()
	      	{

	      		try
			{
				// Read from the connection
  				//sampleStruct a;
                auto bytesRead = read(connection, buffer, 100);

  				std::cout << "The message was: " << buffer << std::endl;
			}
			catch(std::exception& e)
			{
			    std::cerr << e.what() << endl;
			}


	      	}


	private:
		int sockfd;
		// Listen to port 9999 on any address
		int port= 9999;
  		sockaddr_in sockaddr;

		int connection;
		char buffer[1000];



};


int main(int argc, char *argv[])
{
  Server server1;
  server1.receiveMessages();
  server1.receiveMessages();
  return 0;
}

