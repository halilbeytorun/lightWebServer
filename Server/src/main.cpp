#include "InitiationDispatcher.h"
#include "LoggingAcceptor.h"
#include "EventType.h"

#include "hutiliy.h"

#include <thread>
#include <atomic>

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>






int main()
{
    LoggingAcceptor acceptor{};
    auto retval = acceptor.create_server();

    retval = InitiationDispatcher::getInstance()->register_handler(&acceptor, ACCEPT_EVENT);


    std::atomic<bool> reactor_done(false);
    std::thread handlerThread([&reactor_done](){
        while(!reactor_done)
        {
            InitiationDispatcher::getInstance()->handle_events(15);
        }
    });


    //reactor_done = true;
    handlerThread.join();
    acceptor.destroy_server();

    retval = InitiationDispatcher::getInstance()->remove_handler(&acceptor, ACCEPT_EVENT);

}

