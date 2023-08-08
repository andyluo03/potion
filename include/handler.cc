#include "handler.hh"

#include "http_request.hh"

#include <string>
#include <map>
#include <memory>
#include <string>
#include <cstring>
#include <iostream>

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

namespace potion {

Handler::Handler() : thread_pool_ {std::make_unique<std::counting_semaphore<8>>(8)} {}

int Handler::handle_connection(int fd){
    thread_pool_->acquire();
    char* raw_request = (char*) malloc(4096);
    size_t len = recv(fd, raw_request, 4096, 0);
    HttpRequest request(std::string(raw_request, len));
    free(raw_request);

    std::string result = "HTTP/1.1 404 OK\nContent-Type: text/plain\n\nPath: " +
                            request.uri().path() + " not found!";

    if(this->router_.find(request.uri().path()) != this->router_.end()){
        result = this->router_[request.uri().path()](request);
    }

    send(fd, result.c_str(), result.size(), 0);
    close(fd);
    thread_pool_->release();
    return 1;
}

int Handler::add_route(std::string route, 
                        std::function<std::string(potion::HttpRequest)> func)
{
    if(this->router_.find(route) != this->router_.end())
        return -1;
    
    this->router_[route] = func;
    return 1;
}

}