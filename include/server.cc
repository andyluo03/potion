#include "server.hh"

#include "connection.hh"

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

namespace potion {
Server::Server (int port) : PORT {port}, 
                    thread_pool {std::make_unique<std::counting_semaphore<5>>(0)} {} //Probably switch to application factory!

int Server::add_route(std::string route, std::function<std::string(std::string temporary)> handler) {
    if(router.find(route) != router.end()){
        std::cout << "Route already exists! Overwriting...";
    }
    router[route] = handler;
    return 1;
}

void Server::start () {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int address_length = sizeof(struct sockaddr_in);

    if(server_fd == 0) {
        std::cout << "Socket Error";
        return;
    }

    struct sockaddr_in address = {
        .sin_family = AF_INET, 
        .sin_port = htons(PORT),
    };

    address.sin_addr.s_addr = INADDR_ANY;

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
        auto route = router["Hello World"];
        std::thread handler(potion::connection::handle_connection, request_fd, route);
        handler.detach();
    }
}
}
