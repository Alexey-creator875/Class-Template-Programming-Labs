#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace {
const size_t kDefaultVectorCapacity = 8;
const size_t kGrowthFactor = 2;
const size_t kReductionFactor = 4;
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
            vector[i] = vector[i + 1];
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

            for (size_t j = 0; j < size - i - 1; ++j) {
                if (vector[j] > vector[j + 1]) {
                    std::swap(vector[j], vector[j + 1]);
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