#include "include/server.hh"

int main () {
    potion::Server app(8080);
    app.start();
}