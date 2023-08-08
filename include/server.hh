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

    void start ();

    Handler handler_;

    private:
    const int PORT;
    std::unique_ptr<std::counting_semaphore<5>> thread_pool;
};
}

#endif
