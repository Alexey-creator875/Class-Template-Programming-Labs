#include <iostream>

#include "FractionExecutor.h"

int main() {
    try {
        FractionExecutor::RunApplication();
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}
