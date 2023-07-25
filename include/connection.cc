#include "connection.hh"

#include <sys/socket.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

namespace potion {
namespace connection {

int handle_connection(int fd, std::function<std::string(std::string)> handler){
    char* buffer = (char*) malloc(4096);
    int len = recv(fd, buffer, 4096, 0);
    std::string message(buffer, len);
    free(buffer);
    std::string output = handler(message);
    send(fd, output.c_str(), output.size(), 0);
    std::cout << message;
    close(fd);
    return 1;
}

}
}
