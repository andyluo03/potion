#ifndef POTION_CONNECTION_H
#define POTION_CONNECTION_H

#include <functional>
#include <string>

namespace potion {
namespace connection {
int handle_connection(int fd, std::function<std::string(std::string)> handler);
}
}

#endif
