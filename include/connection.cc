#ifndef POTION_CONNECTION
#define POTION_CONNECTION

#include "connection.hh"

#include <sys/socket.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

namespace potion {
namespace http {
int handle_connection (int fd) {
    char* buffer = (char*) malloc(4096);
    int len = recv(fd, buffer, 4096, 0);
    std::string message(buffer, len);
    free(buffer);
    std::string test = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    send(fd, test.c_str(), test.size(), 0);
    std::cout << message;
    close(fd);
    return 1;
}
}
}

#endif
