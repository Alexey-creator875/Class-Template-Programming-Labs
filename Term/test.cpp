#include "Term.h"

#include <iostream>

int main() {
    Term term;
    Term term1(7);
    Term term2(-7, 3);
    Term term3(-7, -3);

    std::cout << term << '\n';
    std::cout << term1 << '\n';
    std::cout << term2 << '\n';
    std::cout << term3 << '\n';

    return 0;
}
