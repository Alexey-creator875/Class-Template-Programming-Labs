#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace {
const size_t kDefaultVectorCapacity = 8;
const size_t kGrowthFactor = 2;
const size_t kReductionFactor = 4;
}  // namespace

template<class T>
int Compare(const T first, const T second) {
    if (first == second) {
        return 0;
    }

    if (first < second) {
        return -1;
    }

    return 1;
}

template<class T>
class MyVector {
 protected:
    size_t size;
    size_t capacity;
    T* vector;

 private:
    void resize();

 public:
    MyVector();
    MyVector(const T element);
    MyVector(const MyVector& object);

    ~MyVector();

    int length();

    void pushBack(const T element);
    void deleteElement(const int index);
    int findElement(const T element);
    void sort(bool ascending = true);

    T operator[](int index) const;
    T& operator[](const int index);
    MyVector& operator=(const MyVector& object);

    template<class F>
    friend std::ostream& operator<<(std::ostream& out, const MyVector<F>& object);
};

template<class T>
void MyVector<T>::resize() {
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

template<class T>
MyVector<T>::MyVector() {
    capacity = kDefaultVectorCapacity;
    size = 0;
    vector = new T[kDefaultVectorCapacity];
}

template<class T>
MyVector<T>::MyVector(const T element) {
    capacity = kDefaultVectorCapacity;
    size = 0;
    vector = new T[kDefaultVectorCapacity];
    pushBack(element);
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& object) {
    capacity = object.capacity;
    size = 0;
    vector = new T[object.capacity];

    for (size_t i = 0; i < object.size; ++i) {
        pushBack(object[i]);
    }
}

template<class T>
MyVector<T>::~MyVector() {
    delete[] vector;
}

template<class T>
int MyVector<T>::length() {
    return static_cast<int>(size);
}

template<class T>
void MyVector<T>::pushBack(const T element) {
    if (size >= capacity) {
        resize();
    }

    vector[size++] = element;
}

template<class T>
void MyVector<T>::deleteElement(const int index) {
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

template<class T>
int MyVector<T>::findElement(const T element) {
    for (size_t i = 0; i < size; ++i) {
        if (!Compare(vector[i], element)) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

template<class T>
void MyVector<T>::sort(bool ascending) {
    bool sorted = false;

    for (size_t i = 0; i < size && !sorted; ++i) {
        sorted = true;

        for (size_t j = 0; j < size - i - 1; ++j) {
            if (ascending? Compare(vector[j], vector[j + 1]) > 0 : Compare(vector[j], vector[j + 1]) < 0) {
                std::swap(vector[j], vector[j + 1]);
                sorted = false;
            }
        }
    }
}

template<class T>
T MyVector<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::runtime_error("index out of boundary");
    }

    return vector[index];
}

template<class T>
T& MyVector<T>::operator[](const int index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("index out of boundary");
    }

    return *(vector + index);
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& object) {
    if (vector) {
        delete[] vector;
    }

    capacity = object.capacity;
    size = 0;
    vector = new T[object.capacity];

    for (size_t i = 0; i < object.size; ++i) {
        pushBack(object[i]);
    }

    return *this;
}

template<class F>
std::ostream& operator<<(std::ostream& out, const MyVector<F>& object)  {
    for (size_t i = 0; i < object.size; ++i) {
        out << object[i] << ' ';
    }

    return out;
}
