#ifndef POTION_SERVER
#define POTION_SERVER

#include "handler.hh"

#include <semaphore>
#include <memory>
#include <thread>
#include <iostream>
#include <functional>
#include <map>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace potion {
class Server {
public:
Server (int port);

Server (Server &other) = delete;
Server () = delete;
void operator=(const Server&) = delete;

static void start ();

static int add_route(std::string route, 
                        std::function<std::string(potion::HttpRequest)> func);

static Handler handler_;
static int port_;
void static cleanup (int signum);
};
}

#endif
