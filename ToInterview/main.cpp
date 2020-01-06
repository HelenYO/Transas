#include <iostream>

#include "Worker.h"

int main() {
    unsigned long threads = std::thread::hardware_concurrency();
    if(threads == 0) {
        threads = 2;
    }
    Worker work(threads);
    work.run(30);
    return 0;
}