#include <chrono>
#include <cstdio>

int main() {
    using namespace std::chrono;
    auto start_time = steady_clock::now();

    //Do something
    printf("Hello, World!\n");

    auto tmp = steady_clock::now() - start_time;
    printf("%ld", tmp);
    return 0;
};
