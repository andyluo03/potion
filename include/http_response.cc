#include "http_response.hh"

#include <sstream>


namespace potion {

// could make this a switch statement instead, not sure which one is faster when there are a lot of cases
const std::unordered_map<unsigned int, std::string> HttpResponse::status_code_map_ = {
    // ** 1xx Informational **
    { 100,       "Continue" },
    { 101,       "Switching Protocols" },
    { 102,       "Processing" },
    { 103,       "Early Hints" },
    // ** 2xx Success **
    { 200,       "OK" },
    { 201,       "Created" },
    { 202,       "Accepted" },
    { 203,       "Non-Authoritative Information" },
    { 204,       "No Content" },
    { 205,       "Reset Content" },
    { 206,       "Partial Content" },
    { 207,       "Multi-Status" },
    { 208,       "Already Reported" },
    { 226,       "IM Used" },
    // ** 3xx Redirection **
    { 300,       "Multiple Choices" },
    { 301,       "Moved Permanently" },
    { 302,       "Found" },
    { 303,       "See Other" },
    { 304,       "Not Modified" },
    { 305,       "Use Proxy" },
    { 307,       "Temporary Redirect" },
    { 308,       "Permanent Redirect" },
    // ** 4xx Client Error **
    { 400,       "Bad Request" },
    { 401,       "Unauthorized" },
    { 402,       "Payment Required" },
    { 403,       "Forbidden" },
    { 404,       "Not Found" },
    { 405,       "Method Not Allowed" },
    { 406,       "Not Acceptable" },
    { 407,       "Proxy Authentication Required" },
    { 408,       "Request Timeout" },
    { 409,       "Conflict" },
    { 410,       "Gone" },
    { 411,       "Length Required" },
    { 412,       "Precondition Failed" },
    { 413,       "Payload Too Large" },
    { 414,       "URI Too Long" },
    { 415,       "Unsupported Media Type" },
    { 416,       "Range Not Satisfiable" },
    { 417,       "Expectation Failed" },
    { 418,       "I'm a teapot" },
    { 421,       "Misdirected Request" },
    { 422,       "Unprocessable Entity" },
    { 423,       "Locked" },
    { 424,       "Failed Dependency" },
    { 426,       "Upgrade Required" },
    { 428,       "Precondition Required" },
    { 429,       "Too Many Requests" },
    { 431,       "Request Header Fields Too Large" },
    { 444,       "Connection Closed Without Response" },
    { 451,       "Unavailable For Legal Reasons" },
    { 499,       "Client Closed Request" },
    // ** 5xx Server Error **
    { 500,       "Internal Server Error" },
    { 501,       "Not Implemented" },
    { 502,       "Bad Gateway" },
    { 503,       "Service Unavailable" },
    { 504,       "Gateway Timeout" },
    { 505,       "HTTP Version Not Supported" },
    { 506,       "Variant Also Negotiates" },
    { 507,       "Insufficient Storage" },
    { 508,       "Loop Detected" },
    { 510,       "Not Extended" },
    { 511,       "Network Authentication Required" },
    { 500,       "Internal Server Error" },
    { 501,       "Not Implemented" },
    { 502,       "Bad Gateway" },
    { 503,       "Service Unavailable" },
    { 504,       "Gateway Timeout" },
    { 505,       "HTTP Version Not Supported" },
    { 506,       "Variant Also Negotiates" },
    { 507,       "Insufficient Storage" },
    { 508,       "Loop Detected" },
    { 510,       "Not Extended" },
    { 511,       "Network Authentication Required" },
};

HttpResponse::HttpResponse(unsigned int status_code) {
    status_code_ = status_code;
    headers_["Content-Type"] = "text/html";
    headers_["Content-Length"] = "0";
}

std::string HttpResponse::ToString() {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << status_code_ << " " << status_code_map_.at(status_code_) << "\r\n";
    for (auto& [key, value] : headers_) {
        oss << key << ": " << value << "\r\n";
    }
    oss << "\r\n";
    oss << body_;
    return oss.str();
}



} // namespace potion