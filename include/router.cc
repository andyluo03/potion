#include "router.hh"

#include <functional>
#include <map>
#include <string>

namespace potion {
    Router::Router(){}

    std::function<std::string(std::string temporary)> Router::operator[](std::string route){
        return routes[route];
    }
};
