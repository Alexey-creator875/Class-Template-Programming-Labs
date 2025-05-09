#include "Polynomial.h"

#include <cstring>
#include <iostream>
#include <cstddef>
#include <stdexcept>

namespace {
const int kDeffaultTermCoefficient = 0;
const int kDeffaultTermDegree = 0;

const int kTermAbsoluteCoefficientNotRequiredExplicitIndication = 1;
const int kTermDegreeNotRequiredExplicitIndication = 1;

const int kDeffaultPolynomialDegree = 0;

const int kTermBufferSize = 20;
const int kPolynomialBufferSize = 50;

char* FindNewTermStart(char* string) {
    char* plus = std::strchr(string, '+');
    char* minus = std::strchr(string, '-');

    if (plus && minus) {
        return (plus < minus)? plus : minus;
    }

    if (plus) {
        return plus;
    }

    if (minus) {
        return minus;
    }

    return std::strchr(string, '\0');
    
}

Term CreateTermBasedOnString(char* string) {
    if (!std::strchr(string, 'x')) {
        return Term(std::stoi(string), kDeffaultTermDegree);
    }

    int coefficient = 0;

    if (string[0] == 'x' || (string[0] == '+' && string[1] == 'x')) {
        coefficient = kTermAbsoluteCoefficientNotRequiredExplicitIndication;
    } else if ((string[0] == '-') && (string[1] == 'x')) {
        coefficient = -kTermAbsoluteCoefficientNotRequiredExplicitIndication;
    } else {
        coefficient = std::stoi(string);
    }

    if (!(std::strchr(string, '^'))) {
        return Term(coefficient, kTermDegreeNotRequiredExplicitIndication);
    }

    int degree = std::stoi(std::strchr(string, '^') + 1);

    return Term(coefficient, degree);
}

void removeSpaces(char* string) {
    char* newString = new char[std::strlen(string) + 1]{};

    size_t newStringIndex = 0;
    
    for (size_t i = 0; i < kTermBufferSize && string[i]; ++i) {
        if (string[i] != ' ') {
            newString[newStringIndex] = string[i];
            ++newStringIndex;
        }
    }

    std::strcpy(string, newString);
    delete[] newString;
}
}  // namespace

int Term::getCoefficient() const {
    return coefficient;
}

int Term::getDegree() const {
    return degree;
}

Term& Term::operator*=(const Term& object) {
    coefficient *= object.coefficient;
    degree += object.degree;
    return *this;
}

Term operator+(const Term& first, const Term& second) {
    if (first.degree != second.degree) {
        throw std::runtime_error("failed to add two terms of different degrees");
    }

    return Term(first.coefficient + second.coefficient, first.degree);
}

[[maybe_unused]] Term operator*(const Term& first, const Term& second) {
    return Term(first.coefficient * second.coefficient, first.degree + second.degree);
}

bool operator==(const Term& first, const Term& second) {
    return (first.coefficient == second.coefficient) && (first.degree == second.degree);
}

bool operator<(const Term& first, const Term& second) {
    return (first.degree < second.degree) || ((first.degree == second.degree) && (first.coefficient == second.coefficient));
}

std::ostream& operator<<(std::ostream& out, const Term& object) {
    if (object.coefficient == kDeffaultTermCoefficient) {
        out << '0';
        return out;
    }

    if ((std::abs(object.coefficient) != kTermAbsoluteCoefficientNotRequiredExplicitIndication) || (object.degree == kDeffaultTermDegree)) {
        out << object.coefficient;
    }

    switch (object.degree) {
        case kDeffaultTermDegree:
            break;
        case kTermDegreeNotRequiredExplicitIndication:
            out << 'x';
            break;
        default:
            out << "x^" << object.degree;
            break;
    }

    return out;
}

std::istream& operator>>(std::istream& in, Term& object) {
    char buffer[kTermBufferSize];
    in.getline(buffer, kTermBufferSize, '\n');

    object = CreateTermBasedOnString(buffer);

    return in;
}

Polynomial::Polynomial() {
    poly.pushBack(Term());
    degree = kDeffaultPolynomialDegree;
}

Polynomial::Polynomial(int number) {
    poly.pushBack(Term(number));
    degree = kDeffaultPolynomialDegree;
}

Polynomial::Polynomial(const Term& term) {
    poly.pushBack(term);
    degree = term.degree;
}

Polynomial& Polynomial::operator=(const Polynomial& object) {
    poly = object.poly;
    degree = object.degree;

    return *this;
}

void Polynomial::changeOrder() {
    order = !order;

    poly.sort(order);
}

Polynomial& Polynomial::operator+=(const Term& object) {
    if (object.degree > degree) {
        poly.pushBack(object);
        degree = object.degree;
        poly.sort(order);
        return *this;
    }

    // Binary Search better

    for (size_t i = 0; i < poly.length(); ++i) {
        if (poly[i].degree == object.degree) {
            if (poly[i].coefficient == -object.coefficient) {
                poly.deleteElement(i);
                return *this;
            }

            poly[i].coefficient += object.coefficient;
            return *this;
        }
    }

    poly.pushBack(object);
    poly.sort(order);

    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& object) {
    Polynomial newPolynomial = *this;

    for (size_t i = 0; i < object.poly.length(); ++i) {
        newPolynomial += object.poly[i];
    }

    *this = newPolynomial;

    return *this;
}

Polynomial& Polynomial::operator*=(const Term& object) {
    if (object.coefficient == kDeffaultTermCoefficient) {
        *this = 0;
        return *this;
    }

    for (size_t i = 0; i < poly.length(); ++i) {
        poly[i] *= object;
    }

    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& object) {
    if ((object.poly.length() == 1) && (object.poly[0].coefficient == 0)) {
        *this = 0;
        return *this;
    }

    Polynomial newPolinomial;

    for (size_t i = 0; i < object.poly.length(); ++i) {
        Polynomial temp = *this;
        temp *= object.poly[i];
        newPolinomial += temp;
    }

    *this = newPolinomial;
    return *this;
}

Polynomial operator+(const Polynomial& first, const Polynomial& second) {
    Polynomial newPolinomial = first;
    newPolinomial += second;

    return newPolinomial;
}

Polynomial operator*(const Polynomial& first, const Polynomial& second) {
    Polynomial newPolinomial = first;
    newPolinomial *= second;

    return newPolinomial;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& object) {
    if (!object.poly.length()) {
        throw std::runtime_error("invalid polynomial");
    }

    out << object.poly[0];

    for (size_t i = 1; i < object.poly.length(); ++i) {
        if (object.poly[i].getCoefficient() > 0) {
            out << " + " << object.poly[i];
            continue;
        }

        if (object.poly[i].getCoefficient() < 0) {
            out << " - " << Term(-object.poly[i].getCoefficient(), object.poly[i].getDegree());
        }
    }

    return out;
}

std::istream& operator>>(std::istream& in, Polynomial& object) {
    object = 0;

    char buffer[kPolynomialBufferSize]{};
    in.getline(buffer, kPolynomialBufferSize, '\n');

    char* currentTermStart = buffer;

    while (*currentTermStart == ' ') {
        ++currentTermStart;
    }

    while (*currentTermStart != '\0') {
        char* nextTermStart = FindNewTermStart(currentTermStart + 1);

        char currentTerm[kTermBufferSize]{};
        std::copy(currentTermStart, nextTermStart, currentTerm);

        removeSpaces(currentTerm);

        Term term = CreateTermBasedOnString(currentTerm);

        object += term;

        currentTermStart = nextTermStart;
    }    

    return in;
}
