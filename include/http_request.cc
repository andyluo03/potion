#include "http_request.hh"

#include <sstream>
#include <iostream>


namespace potion {

HttpRequest::HttpRequest(const std::string& raw_request) {
    ParseRequest(raw_request);
}

void HttpRequest::ParseRequest(const std::string& raw_request) {
    // input is a raw http request
    // format: 
    //
    // GET /path HTTP/1.1\r\n
    // Host: localhost:8080\r\n
    // Content-Type: application/json\r\n
    // Content-Length: 36\r\n
    // \r\n
    // this is the request body
    
    std::string request_line, headers, body;
    size_t start = 0, end = 0;
    
    // get request line
    end = raw_request.find("\r\n");
    request_line = raw_request.substr(start, end - start);
    start = end + 2;

    // get headers
    if (raw_request.size() > start) {
        std::string header_line = raw_request.substr(start,raw_request.size() - 1);
        end = header_line.find("\r\n\r\n");
        headers = raw_request.substr(start, end);
        start = start + end + 4;
    }

    // get body
    if (raw_request.size() > start) {
        body = raw_request.substr(start);
    }

    ParseRequestLine(request_line);
    ParseHeaders(headers);
    body_ = body;
    std::cout << body << std:: endl;

    //std::cout << uri_.path() << std::endl;
    //std::cout << uri_.host() << std::endl;
    //std::cout << uri_.port() << std::endl;
    //std::cout << uri_.uri() << std::endl;
}

void HttpRequest::ParseRequestLine(const std::string& req_line) {
    // format: GET /path HTTP/1.1

    std::istringstream iss(req_line);
    std::string method, path, version;
    iss >> method >> path >> version;
    method_ = StringToMethod(method);
    uri_.SetPath(path);
    version_ = StringToVersion(version);

    std::cout << method << " " << path << " " << version << std::endl;
}

void HttpRequest::ParseHeaders(const std::string& headers) {
    // format: 
    // Host: localhost:8080\r\n
    // Content-Type: application/json\r\n
    // Content-Length: 36\r\n
    if(headers == ""){
        return;
    }
    std::istringstream iss(headers);
    std::string line;
    while (std::getline(iss, line)) {
        // remove \r
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        // get key and value
        size_t pos = line.find(":");
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 2);

        // add host and port to uri
        if (key == "Host") {
            size_t pos = value.find(":");
            std::string host = value.substr(0, pos);
            std::string port = value.substr(pos + 1);
            uri_.SetHost(host);
            uri_.SetPort(port);
        }

        std::cout << key << " " << value << std::endl;

        headers_[key] = value;
    }
}


HttpMethod HttpRequest::StringToMethod(const std::string& method) {
    if (method == "GET") {
        return HttpMethod::GET;
    } else if (method == "POST") {
        return HttpMethod::POST;
    } else if (method == "PUT") {
        return HttpMethod::PUT;
    } else if (method == "DELETE") {
        return HttpMethod::DELETE;
    } else if (method == "HEAD") {
        return HttpMethod::HEAD;
    } else if (method == "OPTIONS") {
        return HttpMethod::OPTIONS;
    } else if (method == "CONNECT") {
        return HttpMethod::CONNECT;
    } else if (method == "TRACE") {
        return HttpMethod::TRACE;
    } else if (method == "PATCH") {
        return HttpMethod::PATCH;
    } else {
        throw std::invalid_argument("Invalid HTTP method");
    }
}

HttpVersion HttpRequest::StringToVersion(const std::string& version) {
    if (version == "HTTP/1.0") {
        return HttpVersion::HTTP_1_0;
    } else if (version == "HTTP/1.1") {
        return HttpVersion::HTTP_1_1;
    } else if (version == "HTTP/2.0") {
        return HttpVersion::HTTP_2_0;
    } else {
        throw std::invalid_argument("Invalid HTTP version");
    }
}


}
