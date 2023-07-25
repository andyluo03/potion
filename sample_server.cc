#include "include/server.hh"

int main () {
    potion::Server app(8080);

    app.add_route("Hello World", [](std::string a) -> std::string {
        return "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    });

    app.start();
}