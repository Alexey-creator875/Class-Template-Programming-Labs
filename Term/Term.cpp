#include "Term.h"

#include <stdexcept>
#include <iostream>

namespace {
const int kDeffaultTermCoefficient = 0;
const int kDeffaultTermDegree = 0;
const int kTermDegreeNotRequiredExplicitIndication = 1;
}

Term operator+(const Term& first, const Term& second) {
    if (first.degree != second.degree) {
        throw std::runtime_error("failed to add two terms of different degrees");
    }

    return Term(first.coefficient + second.coefficient, first.degree);
}

std::ostream& operator<<(std::ostream& out, const Term& object) {
    if (object.coefficient == kDeffaultTermCoefficient) {
        out << '0';
        return out;
    }

    switch(object.degree) {
        case kDeffaultTermDegree:
            out << object.coefficient;
            break;
        case kTermDegreeNotRequiredExplicitIndication:
            out << object.coefficient << 'x';
            break;
        default:
            out << object.coefficient << "x^" << object.degree;
            break;
    }

    return out;
}