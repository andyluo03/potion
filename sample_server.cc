#include "include/server.hh"
#include "include/http_request.hh"
#include "include/http_response.hh"

#include <string>
// #include <iostream>

int main () {
    potion::Server app(8080);

    app.add_route("/test", [](potion::HttpRequest a) -> std::string {
        potion::HttpResponse response(200);
        response.set_body("GG EZ");
        response.set_content_type("text/plain");

        // std::cout << response.ToString() << std::endl;

        return response.ToString();
    });

    app.add_route("/foo", [](potion::HttpRequest a) -> std::string {
        potion::HttpResponse response(200);
        response.set_body("bar");
        response.set_header("X-Test", "test");
        return response.ToString();
    });

    app.start();
}