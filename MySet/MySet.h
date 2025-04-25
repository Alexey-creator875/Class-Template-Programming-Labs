#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace {
const size_t kDefaultVectorCapacity = 8;
const size_t kGrowthFactor = 2;
const size_t kReductionFactor = 4;

const size_t kUnit = 1;

const size_t kHalfDivisor = 2;
}  // namespace

template<class T>
class MyVector {
 protected:
    size_t size;
    size_t capacity;
    T* vector;

 private:
    void resize() {
        if (size >= capacity) {
            capacity *= kGrowthFactor;
        } else if (size < (capacity / kReductionFactor)) {
            capacity /= kReductionFactor;
        } else {
            return;
        }

        T* buffer = vector;
        vector = new T[capacity];
        std::copy(buffer, buffer + size, vector);
        delete[] buffer;
        return;
    }

 public:
    MyVector() {
        capacity = kDefaultVectorCapacity;
        size = 0;
        vector = new T[kDefaultVectorCapacity];
    }
    MyVector(const T& element) : MyVector() {
        *vector = element;
        ++size;
    }

    MyVector(const MyVector& object) {
        capacity = object.capacity;
        size = object.size;
        vector = new T[capacity];
        std::copy(object.vector, object.vector + object.size, vector);
    }

    ~MyVector() { delete[] vector; }

    void pushBack(const T& element) {
        if (size >= capacity) {
            resize();
        }

        vector[size++] = element;
    }

    void deleteElement(const int index) {
        if (index < 0 || index >= size) {
            throw std::runtime_error("index out of boundary");
        }

        --size;

        for (size_t i = static_cast<size_t>(index); i < size; ++i) {
            vector[i] = vector[i + kUnit];
        }

        if (capacity > kDefaultVectorCapacity && size < (capacity / kReductionFactor)) {
            resize();
        }
    }

    int findElement(const T& element) {
        for (size_t i = 0; i < size; ++i) {
            if (vector[i] == element) {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    void sort() {
        bool sorted = false;

        for (size_t i = 0; i < size && !sorted; ++i) {
            sorted = true;

            for (size_t j = 0; j < size - i - kUnit; ++j) {
                if (vector[j] > vector[j + kUnit]) {
                    std::swap(vector[j], vector[j + kUnit]);
                    sorted = false;
                }
            }
        }
    }

    T operator[](const int index) const {
        if (index < 0 || index >= size) {
            throw std::runtime_error("index out of boundary");
        }

        return vector[index];
    }

    T& operator[](const int index) {
        if (index < 0 || index >= size) {
            throw std::runtime_error("index out of boundary");
        }

        return *(vector + index);
    }

    MyVector& operator=(const MyVector& object) {
        if (vector) {
            delete[] vector;
        }

        capacity = object.capacity;
        size = object.size;
        vector = new T[object.capacity];

        std::copy(object.vector, object.vector + object.size, vector);

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const MyVector& object) {
        for (size_t i = 0; i < object.size; ++i) {
            out << object[i] << ' ';
        }

        return out;
    }
};

template<class T>
class MySet : protected MyVector<T> {
 private:
    int findElement(const T& element) const {
        if (this->size == 0) {
            return -1;
        }

        size_t leftBoundary = 0;
        size_t rightBoundary = this->size - kUnit;

        while ((rightBoundary - leftBoundary) > kUnit) {
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

        for (size_t i = 0; i < object.size - kUnit; ++i) {
            out << object[i] << ", ";
        }

        out << object[object.size - kUnit] << '}';

        return out;
    }
};
