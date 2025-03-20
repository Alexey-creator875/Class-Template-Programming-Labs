#pragma once

#include <iostream>

class Fraction {
 private:
    int numerator;
    int denominator;

    void reduce();

 public:
    Fraction();
    Fraction(int numerator, int denominator);
    Fraction(double number);
    Fraction(const char* string);

    void setNumerator(int numerator);
    void setDenominator(int denominator);
    int getNumerator();
    int getDenominator();

    friend std::ostream& operator<<(std::ostream& out, const Fraction& object);
    friend std::istream& operator>>(std::istream& in, Fraction& object);

    Fraction operator+(const Fraction& second);
    Fraction& operator+=(const Fraction& second);
    Fraction& operator-=(const Fraction& second);
    friend Fraction operator+(const double first, const Fraction& second);
};
