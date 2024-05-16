#include "../../Server/src/hutiliy.h"


#include <thread>

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void serverConnection(int threadNumber)
{
    
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024] = {0};

    // Create a socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        return;
    }

    // Set the server address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return;
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        return;
    }

    sleep(5);

    // Send a message to the server
    std::string message = std::string("GET / HTTP/1.1\n");
    Logger("LoggingAcceptorTest", message, " message is sent!");
    
    if (send(clientSocket, message.c_str(), message.length(), 0) < 0) {
        perror("Send failed");
        return;
    }

    sleep(1);
    close(clientSocket);
    sleep(1);

}



int main()
{
    serverConnection(1);
}

