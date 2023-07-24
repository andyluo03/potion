#include "include/server.cc"

int main () {
    potion::Server app(8080);
    app.start();
}