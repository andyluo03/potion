#ifndef POTION_SERVER
#define POTION_SERVER

#include <semaphore>
#include <memory>
#include <thread>
#include <iostream>
#include <functional>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "router.hpp"
#include "connection.hpp"

namespace potion {
class Server {
    const int PORT;
    std::counting_semaphore<5>* thread_pool; //pretty sure this is unnecessary
    potion::Router router;

    public:
    Server (int port) : PORT {port}, 
                        thread_pool {new std::counting_semaphore<5>(0)} {} //Probably switch to application factory!
    
    int add_route(std::string route, std::function<std::string(std::string temporary)> handle) {
        router[route] = handle;
        return 1;
    }

    void start () {
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        int address_length = sizeof(struct sockaddr_in);

        if(server_fd == 0) {
            std::cout << "Socket Error";
            return;
        }

        struct sockaddr_in address = {
            .sin_family = AF_INET, 
            .sin_addr.s_addr = INADDR_ANY, 
            .sin_port = htons(PORT)
        };

        memset(address.sin_zero, '\0', sizeof(address.sin_zero));

        if (bind(server_fd, (struct sockaddr* )&address, sizeof(address)) < 0) {
            std::cout << "Bind Error";
            return;
        }

        if (listen(server_fd, 10) < 0) {
            std::cout << "Listen error";
            return;
        }
        
        while (true) {
            int request_fd = accept(server_fd, (struct sockaddr * )&address, (socklen_t*)&address_length);
            std::thread request_handler(potion::http::handle_connection, request_fd);
            request_handler.detach();
        }
    }
};
}

#endif
