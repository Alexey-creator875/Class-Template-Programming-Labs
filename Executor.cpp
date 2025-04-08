#include "Executor.h"
#include "Stack/MyStack.h"

#include <iostream>
#include <stdexcept>

namespace {

}

namespace Executor {
void RunApplication() {
    int number = 0;
    std::cout << "Enter natural number:\n";
    std::cin >> number;

    if (number <= 0) {
        throw std::runtime_error("invalid number for prime factorization");
    }

    int buffer = number;
    MyStack<int> stack;

    for (int i = 2; (buffer != 1) && (i < number); ++i) {
        while (buffer % i == 0) {
            stack.push(i);
            buffer /= i;
        }
    }

    std::cout << number << " = " << stack << '\n';

    stack.reverse();

    std::cout << number << " = " << stack << '\n';
}
}