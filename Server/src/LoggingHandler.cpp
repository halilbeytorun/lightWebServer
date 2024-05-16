#include "LoggingHandler.h"
#include "hutiliy.h"

#include <unistd.h>
#include <sys/socket.h>
#include <cstdio>
#include <iostream>

LoggingHandler::LoggingHandler(int _clientSocket) : m_clientSocket(_clientSocket), m_socketClosed(false)
{

}
LoggingHandler::~LoggingHandler()
{
    if(!m_socketClosed)
        close(m_clientSocket);
}

int LoggingHandler::get_handle()
{
    return m_clientSocket;
}


int LoggingHandler::handle_event(EventType)
{
    Logger("LoggingHandler::handle_event function");
        // Read data from the client
    int bytesReceived = read(m_clientSocket, buffer, sizeof(buffer));
    if (bytesReceived < 0) {
        perror("Read failed");
        return -1;
    }
    else if(0 == bytesReceived) // Connection closed --> Action needed.
    {
        close(m_clientSocket);
        m_socketClosed = true;
        Logger("LoggingHandler::handle_event client socket is closed from server side!");
        return 0;
    }
    buffer[bytesReceived] = '\0';
    
    std::string_view httpRequest{buffer};
    auto pos = httpRequest.find('\n');
    if(pos != std::string::npos)
    {
        if(std::string(buffer, 0, pos) == std::string{"GET / HTTP/1.1"})
        {
            std::string response{"HTTP/1.1 200 OK\r\n\r\nRequested path: <the path>\r\n"};
            send(m_clientSocket, response.c_str(), response.length(), 0);
            Logger("LoggingHandler::handle_event", response, " is sent");
        }
    }


    return 0;
}
