#include <iostream>

#include "Executor.h"

int main(int, char**) {
    try {
        Executor::RunApplication();  
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
    
    return 0;
}
