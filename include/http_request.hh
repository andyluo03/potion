#ifndef POTION_HTTP_H
#define POTION_HTTP_H

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

// might vause error bc HTTP_1_0 has same value as GET
enum class HttpVersion {
    HTTP_1_0,
    HTTP_1_1,
    HTTP_2_0
};


class HttpRequest {
public:

HttpRequest(const std::string& raw_request);

Uri uri() const { return uri_; }
HttpMethod method() const { return method_; }
HttpVersion version() const { return version_; }
std::string body() const { return body_; }
std::string header(const std::string& key) const { return headers_.at(key); }

private:

void ParseRequest(const std::string& raw_request);
void ParseRequestLine(const std::string& raw_request);
void ParseHeaders(const std::string& raw_request);

HttpMethod StringToMethod(const std::string& method);
HttpVersion StringToVersion(const std::string& version);


// members
HttpMethod method_;
HttpVersion version_;
Uri uri_ = Uri();
std::map<std::string, std::string> headers_;
std::string body_;

};


}

#endif