#pragma once

#include <iostream>

#include "../MyVector/MyVector.h"

class Term {
 protected:
    int coefficient;
    int degree;

    friend class Polynomial;

 public:
    Term(int coefficient = 0, int degree = 0) : coefficient(coefficient), degree(degree) {}

    int getCoefficient() const;
    int getDegree() const;

    Term& operator*=(const Term& object);

    friend Term operator+(const Term& first, const Term& second);
    friend Term operator*(const Term& first, const Term& second);

    friend bool operator==(const Term& first, const Term& second);
    friend bool operator<(const Term& first, const Term& second);

    friend std::ostream& operator<<(std::ostream& out, const Term& object);
    friend std::istream& operator>>(std::istream& in, Term& object);
};

class Polynomial {
 private:
    bool order = false;

 protected:
    MyVector<Term> poly;
    int degree;

 public:
    Polynomial();
    Polynomial(int number);
    Polynomial(const Term& term);
    Polynomial(const Polynomial& polynomial) : poly(polynomial.poly), degree(polynomial.degree) {}

    void changeOrder();

    Polynomial& operator=(const Polynomial& object);

    Polynomial& operator+=(const Term& object);
    Polynomial& operator+=(const Polynomial& object);

    Polynomial& operator*=(const Term& object);
    Polynomial& operator*=(const Polynomial& object);

    friend Polynomial operator+(const Polynomial& first, const Polynomial& second);
    friend Polynomial operator*(const Polynomial& first, const Polynomial& second);

    friend std::ostream& operator<<(std::ostream& out, const Polynomial& object);
    friend std::istream& operator>>(std::istream& in, Polynomial& object);
};
