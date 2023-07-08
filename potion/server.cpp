#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <semaphore>
#include <thread>
#include <memory>

namespace potion {
class Server {
    private:
    std::counting_semaphore<5> thread_pool;

    int test(int a){
        thread_pool.acquire();
        std::cout << a << std::endl;
        thread_pool.release();
        return 1;
    }

    std::thread spawn_thread(int n){
        return std::thread([=, this]{this->test(n);});
    }
    
    public:
    Server() : thread_pool {5} {}

    void run(){
        int n;
        std::cin >> n;
        std::thread t = spawn_thread(n);
        t.join();
        std::cout << thread_pool.max();
    }
};
}

int main(){
    std::cout << "TESTING" << std::endl;
    potion::Server a;
    a.run();
}