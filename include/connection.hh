#ifndef POTION_CONNECTION_H
#define POTION_CONNECTION_H

namespace potion {
namespace http {
int handle_connection (int fd);

int handle_connection(int fd, std::function<std::string(std::string)> handler);
}
}

#endif
