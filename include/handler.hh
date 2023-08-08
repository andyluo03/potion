#ifndef POTION_HANDLER_H
#define POTION_HANDLER_H

#include "http_request.hh"

#include <functional>
#include <map>
#include <string>

namespace potion {
class Handler {
public:
int handle_connection(int fd);

//might want to make route a reference
int add_route(std::string route, 
                std::function<std::string(potion::HttpRequest)> func);

private:
std::map<std::string, std::function<std::string(potion::HttpRequest)>> router_;
};
} //potion

#endif
