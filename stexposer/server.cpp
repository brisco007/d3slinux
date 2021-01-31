//#include "server.h"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read

#include <list>
#include "state.h"
#include "g_stagestypes.h"
//#include "Networking.h"
#include <fstream> // to handle files
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
	      	
	      	void receiveFile(){
	      		FILE *fp;
			int ch = 0;
			fp = fopen(fileName.c_str(),"a");
			int words;
			read(connection, &words, sizeof(int));
			//printf("Passed integer is : %d\n" , words);      //Ignore , Line for Testing
			while(ch != words)
		       	{
				read(connection , buffer , 512); 
				fprintf(fp , " %s" , buffer);   
				//printf(" %s %d "  , buffer , ch); //Line for Testing , Ignore
				ch++;
			}
			std::cout << "The new file created is: " << fileName.c_str() << std::endl;
	      	}
	      	
	      	
	      	void readFile(){
	      		string myLine;
	      		ifstream myFile_Handler;
			// File Open in the Read Mode
			myFile_Handler.open(fileName.c_str());

			if(myFile_Handler.is_open())
			{
				// Keep reading the file
				while(getline(myFile_Handler, myLine))
				{
					// print the line on the standard output
					//cout << myLine << endl;
					
				}
			    	// File Close
			    	myFile_Handler.close();
			    	
			    	stateString = myLine;
			 }
			 else
			 {	
			 	cout << "Unable to open the file!" << endl;
			 }
			 
    		
    		
    		}

	      	void receiveMessages()
	      	{

	      		try
			{	
			
			receiveFile();
				// Read from the connection
                	//auto bytesRead = read(connection, buffer, 512);
                	
			readFile();
			//this line is to print the content of the file that we just received
  			std::cout << "the server received: " << stateString.c_str() << std::endl;
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
		char buffer[512];
		string fileName ="receivedArchive.txt";
		State state;
 		string stateString;



};


int main(int argc, char *argv[])
{
  Server server1;
  server1.receiveMessages();
  return 0;
}

