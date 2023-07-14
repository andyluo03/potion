#include "include/server.hpp"

int main () {
    potion::Server app(8080);
    app.start();
}