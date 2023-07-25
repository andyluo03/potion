#ifndef POTION_HTTP_H
#define POTION_HTTP_H

#include <string>
#include <map>
#include <type_traits>

namespace potion {

enum class HttpMethod {
    GET,
    POST,
    PUT,
    DELETE,
    HEAD,
    OPTIONS,
    CONNECT,
    TRACE,
    PATCH
};

// might vause error bc HTTP_1_0 has same value as GET
enum class HttpVersion {
    HTTP_1_0,
    HTTP_1_1,
    HTTP_2_0
};


class HttpRequest {
public:

HttpRequest(const std::string& raw_request);

private:

void ParseRequest(const std::string& raw_request);
HttpMethod StringToMethod();
HttpVersion StringToVersion();

std::string uri() const { return uri_; }
HttpMethod method() const { return method_; }

// members
HttpMethod method_;
HttpVersion version_;
std::string uri_;
std::map<std::string, std::string> headers_;

};
}

#endif