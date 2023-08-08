#include "include/server.hh"
#include "include/http_request.hh"

#include <string>

int main () {
    potion::Server app(8080);

    app.handler_.add_route("/test", [](potion::HttpRequest a) -> std::string {
        return "HTTP/1.1 200 OK\nContent-Type: text/plain\n\ntest";
    });

    app.handler_.add_route("/foo", [](potion::HttpRequest a) -> std::string {
        return "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nbar";
    });

    app.start();
}