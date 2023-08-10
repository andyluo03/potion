#ifndef URI_H
#define URI_H

#include <string>

namespace potion {

class Uri {
public:

void set_path(const std::string& path) { path_ = path; }
void set_host(const std::string& host) { host_ = host; }
void set_port(const std::string& port) { port_ = port; }

std::string path() const { return path_; }
std::string host() const { return host_; }
std::string port() const { return port_; }
std::string uri() const { return host_ + ":" + port_ + path_;}

private:

std::string path_;
std::string host_;
std::string port_;

};


} // namespace potion

#endif