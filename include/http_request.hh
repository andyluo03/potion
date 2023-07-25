#ifndef POTION_HTTP_H
#define POTION_HTTP_H

#include <string>
#include <map>

namespace potion {
class HttpRequest {
public:

HttpRequest(std::string);

private:

std::string method;
std::string uri;
std::map<std::string, std::string> headers;

};
}

#endif