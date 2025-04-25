#include "Executor.h"

#include <stdexcept>
#include <iostream>

int main(int, char**) {
    try {
        Executor::RunApplication();
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}
