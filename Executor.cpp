#include "Executor.h"

#include <iostream>
#include <stdexcept>

#include "Stack/MyStack.h"

namespace {
const int kFirstNonTrivialDivisor = 2;
const int kUnit = 1;

void PrintPrimeFactorizarion(const int number, const MyStack<int>& stack) {
    std::cout << number << " = " << stack << '\n';
}
}  // namespace

namespace Executor {
void Multipliers(int number, MyStack<int>& stack) {
    int buffer = number;

    for (int i = kFirstNonTrivialDivisor; (buffer != kUnit) && (i < number); ++i) {
        while (buffer % i == 0) {
            stack.push(i);
            buffer /= i;
        }
    }
}

void RunApplication() {
    int number = 0;
    std::cout << "Enter natural number:\n";
    std::cin >> number;

    if (number <= 0) {
        throw std::runtime_error("invalid number for prime factorization");
    }

    MyStack<int> stack;
    Multipliers(number, stack);
    std::cout << "\nPrime Factorization:\n";
    PrintPrimeFactorizarion(number, stack);

    stack.reverse();
    PrintPrimeFactorizarion(number, stack);
}
}  // namespace Executor
