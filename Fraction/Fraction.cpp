#include "Fraction.h"

#include <cmath>
#include <cstddef>
#include <cstring>
#include <iostream>

namespace {
const int kDefaultNumeratorValue = 0;
const int kDefaultDenominatorValue = 1;
const int kPrecision = 4;
const int kDecimalBase = 10;

const size_t kBufferSize = 50;

const int kNextSymbol = 1;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}

}  // namespace

void Fraction::reduce() {
    int greatestCommonDivisor = gcd(std::abs(numerator), std::abs(denominator));
    numerator /= greatestCommonDivisor;
    denominator /= greatestCommonDivisor;
}

Fraction::Fraction() {
    numerator = kDefaultNumeratorValue;
    denominator = kDefaultDenominatorValue;
}

Fraction::Fraction(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::runtime_error("division by zero");
    }

    this->numerator = ((denominator < 0) ? -numerator : numerator);
    this->denominator = std::abs(denominator);
    this->reduce();
}

Fraction::Fraction(double number) {
    numerator = static_cast<int>(number * std::pow(kDecimalBase, kPrecision));
    denominator = std::pow(kDecimalBase, kPrecision);
    this->reduce();
}

Fraction::Fraction(const char* string) : Fraction() {   
    if (std::strchr(string, ' ') && std::strchr(string, '/')) {
        denominator = std::stoi(std::strchr(string, '/') + kNextSymbol);

        if (denominator == 0) {
            throw std::runtime_error("division by zero");
        }

        int integerPart = std::stoi(string);
        numerator = (std::abs(integerPart) * denominator + std::stoi(std::strchr(string, ' ') + kNextSymbol)) * ((integerPart < 0) ? -1 : 1);
    }

    if (!std::strchr(string, ' ') && std::strchr(string, '/')) {
        denominator = std::stoi(std::strchr(string, '/') + kNextSymbol);

        if (denominator == 0) {
            throw std::runtime_error("division by zero");
        }

        numerator = std::stoi(string);
    }

    if (!std::strchr(string, '/')) {
        numerator = std::stoi(string);
    }

    this->reduce();
}

void Fraction::setNumerator(int numerator) {
    this->numerator = numerator;
}

void Fraction::setDenominator(int denominator) {
    this->denominator = denominator;
}

int Fraction::getNumerator() {
    return numerator;
}

int Fraction::getDenominator() {
    return denominator;
}

std::ostream& operator<<(std::ostream& out, const Fraction& object) {
    if (object.numerator % object.denominator == 0) {
        out << object.numerator;
        return out;
    }

    if (object.numerator / object.denominator == 0) {
        out << object.numerator << '/' << object.denominator;
        return out;
    }

    out << object.numerator / object.denominator << ' ' << std::abs(object.numerator % object.denominator) << '/' << object.denominator;
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& object) {
    char buffer[kBufferSize]{};
    in.getline(buffer, kBufferSize, '\n');
    object = buffer;
    return in;
}

Fraction Fraction::operator+(const Fraction& second) {
    return Fraction(numerator * second.denominator + second.numerator * denominator, denominator * second.denominator);
}

Fraction& Fraction::operator+=(const Fraction& second) {
    numerator = numerator * second.denominator + second.numerator * denominator;
    denominator *= second.denominator;
    this->reduce();
    return *this;
}

Fraction operator+(const double first, const Fraction& second) {
    return Fraction(first) + second;
}

Fraction& Fraction::operator-=(const Fraction& second) {
    numerator = numerator * second.denominator - second.numerator * denominator;
    denominator *= second.denominator;
    this->reduce();
    return *this;
}
