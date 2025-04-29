#pragma once

#include <iostream>

class Term {
 protected:
    int coefficient;
    int degree;

 public:
    Term(int coefficient = 0, int degree = 0) : coefficient(coefficient), degree(degree) {}

    friend Term operator+(const Term& first, const Term& second);
    friend std::ostream& operator<<(std::ostream& out, const Term& object);
};