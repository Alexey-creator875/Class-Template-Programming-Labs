#pragma once

#include "../MyVector/MyVector.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace {
const size_t kHalfDivisor = 2;
}  // namespace

template<class T>
class MySet : protected MyVector<T> {
 private:
    int findElement(const T element) const;

 public:
    MySet() = default;
    MySet(const T element) : MyVector<T>(element) {}
    MySet(const MySet<T>& object) : MyVector<T>(object) {}

    bool isElement(const T& element) const;
    void append(const T& element);
    void remove(const T& element);

    MySet operator+=(const MySet& object);
    MySet operator-=(const MySet& object);
    MySet operator*=(const MySet& object);

    template<class F>
    friend MySet<F> operator+(const MySet<F>& first, const MySet<F>& second);

    template<class F>
    friend MySet<F> operator-(const MySet<F>& first, const MySet<F>& second);

    template<class F>
    friend MySet<F> operator*(const MySet<F>& first, const MySet<F>& second);

    template<class F>
    friend bool operator==(const MySet<F>& first, const MySet<F>& second);

    template<class F>
    friend std::ostream& operator<<(std::ostream& out, const MySet<F>& object);
};

template<class T>
int MySet<T>::findElement(const T element) const {
    if (this->size == 0) {
        return -1;
    }

    size_t leftBoundary = 0;
    size_t rightBoundary = this->size - 1;

    while ((rightBoundary - leftBoundary) > 1) {
        size_t middle = (leftBoundary + rightBoundary) / kHalfDivisor;

        if (Compare((*this)[middle], element) > 0) {
            rightBoundary = middle;
        } else {
            leftBoundary = middle;
        }
    }

    if (!Compare((*this)[leftBoundary], element)) {
        return static_cast<int>(leftBoundary);
    }

    if (!Compare((*this)[rightBoundary], element)) {
        return static_cast<int>(leftBoundary);
    }

    return -1;
}

template<class T>
bool MySet<T>::isElement(const T& element) const {
    return findElement(element) != -1;
}

template<class T>
void MySet<T>::append(const T& element) {
    if (!isElement(element)) {
        MyVector<T>::pushBack(element);
        MyVector<T>::sort();
    }
}

template<class T>
void MySet<T>::remove(const T& element) {
    if (isElement(element)) {
        MyVector<T>::deleteElement(findElement(element));
    }
}

template<class T>
MySet<T> MySet<T>::operator+=(const MySet<T>& object) {
    for (size_t i = 0; i < object.size; ++i) {
        this->append(object[i]);
    }

    return *this;
}

template<class T>
MySet<T> MySet<T>::operator-=(const MySet<T>& object) {
    for (size_t i = 0; i < object.size; ++i) {
        this->remove(object[i]);
    }

    return *this;
}

template<class T>
MySet<T> MySet<T>::operator*=(const MySet<T>& object) {
    MySet<T> newSet;

    for (size_t i = 0; i < this->size; ++i) {
        if (object.isElement((*this)[i])) {
            newSet.append((*this)[i]);
        }
    }

    *this = newSet;

    return *this;
}

template<class F>
MySet<F> operator+(const MySet<F>& first, const MySet<F>& second) {
    MySet<F> newSet;

    for (size_t i = 0; i < first.size; ++i) {
        newSet.append(first[i]);
    }

    for (size_t i = 0; i < second.size; ++i) {
        newSet.append(second[i]);
    }

    return newSet;
}

template<class F>
MySet<F> operator-(const MySet<F>& first, const MySet<F>& second) {
    MySet<F> newSet;

    for (size_t i = 0; i < first.size; ++i) {
        if (!second.isElement(first[i])) {
            newSet.append(first[i]);
        }
    }

    return newSet;
}

template<class F>
MySet<F> operator*(const MySet<F>& first, const MySet<F>& second) {
    MySet<F> newSet;

    for (size_t i = 0; i < first.size; ++i) {
        if (second.isElement(first[i])) {
            newSet.append(first[i]);
        }
    }

    return newSet;
}

template<class F>
bool operator==(const MySet<F>& first, const MySet<F>& second) {
    if (first.size != second.size) {
        return false;
    }

    for (size_t i = 0; i < first.size; ++i) {
        if (Compare(first[i], second[i])) {
            return false;
        }
    }

    return true;
}

template<class F>
std::ostream& operator<<(std::ostream& out, const MySet<F>& object) {
    if (object.size == 0) {
        out << "{}";
        return out;
    }

    out << '{';

    for (size_t i = 0; i < object.size - 1; ++i) {
        out << object[i] << ", ";
    }

    out << object[object.size - 1] << '}';

    return out;
}
