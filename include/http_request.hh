#ifndef POTION_HTTP_REQ_H
#define POTION_HTTP_REQ_H

#include "uri.hh"

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


class HttpRequest {
public:

HttpRequest(const std::string& raw_request);

Uri uri() const { return uri_; }
HttpMethod method() const { return method_; }
std::string version() const { return "HTTP/1.0"; }
std::string body() const { return body_; }
std::string header(const std::string& key) const { return headers_.at(key); }

private:

void ParseRequest(const std::string& raw_request);
void ParseRequestLine(const std::string& raw_request);
void ParseHeaders(const std::string& raw_request);

HttpMethod StringToMethod(const std::string& method);

// members
HttpMethod method_;
Uri uri_ = Uri();
std::map<std::string, std::string> headers_;
std::string body_;

};


}

#endif