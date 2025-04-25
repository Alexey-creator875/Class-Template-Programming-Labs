#pragma once

#include "../MyVector/MyVector.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace {
const size_t kHalfDivisor = 2;
}  // namespace

template<class T>
class MySet : protected MyVector<T> {
 private:
    int findElement(const T& element) const {
        if (this->size == 0) {
            return -1;
        }

        size_t leftBoundary = 0;
        size_t rightBoundary = this->size - 1;

        while ((rightBoundary - leftBoundary) > 1) {
            size_t middle = (leftBoundary + rightBoundary) / kHalfDivisor;

            if ((*this)[middle] > element) {
                rightBoundary = middle;
            } else {
                leftBoundary = middle;
            }
        }

        if ((*this)[leftBoundary] == element) {
            return static_cast<int>(leftBoundary);
        }

        if ((*this)[rightBoundary] == element) {
            return static_cast<int>(rightBoundary);
        }

        return -1;
    }

 public:
    bool isElement(const T& element) const {
        return findElement(element) != -1;
    }

    void append(const T& element) {
        if (!isElement(element)) {
            MyVector<T>::pushBack(element);
            MyVector<T>::sort();
        }
    }

    void remove(const T& element) {
        if (isElement(element)) {
            MyVector<T>::deleteElement(findElement(element));
        }
    }

    MySet operator+=(const MySet& object) {
        for (size_t i = 0; i < object.size; ++i) {
            this->append(object[i]);
        }

        return *this;
    }

    MySet operator-=(const MySet& object) {
        for (size_t i = 0; i < object.size; ++i) {
            this->remove(object[i]);
        }

        return *this;
    }

    MySet operator*=(const MySet& object) {
        MySet newSet;

        for (size_t i = 0; i < this->size; ++i) {
            if (object.isElement((*this)[i])) {
                newSet.append((*this)[i]);
            }
        }

        *this = newSet;

        return *this;
    }

    friend MySet operator+(const MySet& first, const MySet& second) {
        MySet newSet;

        for (size_t i = 0; i < first.size; ++i) {
            newSet.append(first[i]);
        }

        for (size_t i = 0; i < second.size; ++i) {
            newSet.append(second[i]);
        }

        return newSet;
    }

    friend MySet operator-(const MySet& first, const MySet& second) {
        MySet newSet;

        for (size_t i = 0; i < first.size; ++i) {
            if (!second.isElement(first[i])) {
                newSet.append(first[i]);
            }
        }

        return newSet;
    }

    friend MySet operator*(const MySet& first, const MySet& second) {
        MySet newSet;

        for (size_t i = 0; i < first.size; ++i) {
            if (second.isElement(first[i])) {
                newSet.append(first[i]);
            }
        }

        return newSet;
    }

    friend bool operator==(const MySet& first, const MySet& second) {
        if (first.size != second.size) {
            return false;
        }

        for (size_t i = 0; i < first.size; ++i) {
            if (!(first[i] == second[i])) {
                return false;
            }
        }

        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const MySet& object) {
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
};
