#ifndef POTION_HTTP_RESP_H
#define POTION_HTTP_RESP_H

#include <string>
#include <map>
#include <unordered_map>

namespace potion {

class HttpResponse {
public:
// constructor
HttpResponse(unsigned int status_code);

// modifiers
void set_body(std::string body) { 
    body_ = body;
    headers_["Content-Length"] = std::to_string(body.size());
}
void set_header(std::string key, std::string value) { headers_[key] = value; }
// **TODO: add validation for content type
void set_content_type(std::string content_type) { headers_["Content-Type"] = content_type; }

// accessors
std::string body() const { return body_; }
std::string header(const std::string& key) const { return headers_.at(key); }
unsigned int status_code() const { return status_code_;}

// convert to raw response string
std::string ToString();

private:

// response data
unsigned int status_code_;
std::string body_;
std::map<std::string, std::string> headers_;


// map of status codes to status message strings
static const std::unordered_map<unsigned int, std::string> status_code_map_;

};


} // namespace potion


#endif