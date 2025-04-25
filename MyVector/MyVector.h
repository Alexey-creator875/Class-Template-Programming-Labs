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
}  // namespace

class MyVector {
 private:
    size_t size;
    size_t capacity;
    int* vector;

    void resize() {
        if (size >= capacity) {
            capacity *= kGrowthFactor;
        } else if (size < (capacity / kReductionFactor)) {
            capacity /= kReductionFactor;
        } else {
            return;
        }

        int* buffer = vector;
        vector = new int[capacity];
        std::copy(buffer, buffer + size, vector);
        delete[] buffer;
        return;
    }

 public:
    MyVector() {
        capacity = kDefaultVectorCapacity;
        size = 0;
        vector = new int[kDefaultVectorCapacity];
    }
    MyVector(int element) : MyVector() {
        *vector = element;
        ++size;
    }

    MyVector(const MyVector& object) {
        capacity = object.capacity;
        size = object.size;
        vector = new int[capacity];
        std::copy(object.vector, object.vector + object.size, vector);
    }

    ~MyVector() { delete[] vector; }

    void pushBack(const int element) {
        if (size >= capacity) {
            resize();
        }

        vector[size++] = element;
    }

    bool deleteElement(const int index) {
        if (index < 0 && index >= size) {
            return false;
        }

        --size;

        for (size_t i = static_cast<size_t>(index); i < size; ++i) {
            vector[i] = vector[i + kUnit];
        }

        if (capacity > kDefaultVectorCapacity && size < (capacity / kReductionFactor)) {
            resize();
        }

        return true;
    }

    int findElement(const int element) {
        for (size_t i = 0; i < size; ++i) {
            if (vector[i] == element) {
                return i;
            }
        }

        return -1;
    }

    int operator[](const int index) const {
        if (index < 0 && index >= size) {
            throw std::runtime_error("index out of boundary");
        }

        return vector[index];
    }

    int& operator[](const int index) {
        if (index < 0 && index >= size) {
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
        vector = new int[object.capacity];

        std::copy(object.vector, object.vector + object.size, vector);

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const MyVector& object) {
        for (size_t i = 0; i < object.size; ++i) {
            out << object[i] << ' ';
        }

        return out;
    }

    void print() {
        for (size_t i = 0; i < size; ++i) {
            std::cout << vector[i] << ' ';
        }

        std::cout << '\n';
    }
};
