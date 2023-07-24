#include <functional>
#include <map>
#include <string>

namespace potion {
class Router {
    private:
    std::map<std::string, std::function<std::string(std::string temporary)>> routes;

    public:
    Router();
    std::function<std::string(std::string temporary)> operator[](std::string route);
};
}
