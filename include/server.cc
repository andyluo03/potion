#include "server.hh"

#include "handler.hh"

#include <semaphore>
#include <memory>
#include <thread>
#include <iostream>
#include <functional>
#include <utility>
#include <csignal>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace potion {
Handler Server::handler_;
int Server::port_;

Server::Server (int port)
{
    std::signal(SIGINT, this->cleanup);
    Server::port_ = port;
}

int Server::add_route(std::string route, 
                        std::function<std::string(potion::HttpRequest)> func)
{
    return Server::handler_.add_route(route, func);
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
        .sin_port = htons(Server::port_),
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
        std::thread handle_connection(
            [](int fd){
                handler_.handle_connection(fd);
            }, request_fd);
        handle_connection.detach();
    }
}

void Server::cleanup (int signum) {
    std::cout << "Program interrupted. Cleaning Up..." << std::endl;
    close(Server::port_);
    std::cout << "Exiting..." << std::endl; 
    exit(signum);
}
} //potion
