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
    void sort();

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
    *vector = element;
    ++size;
}

template<>
MyVector<char*>::MyVector(char* string) {
    capacity = kDefaultVectorCapacity;
    size = 0;
    vector = new char*[kDefaultVectorCapacity];
    *vector = new char[std::strlen(string) + 1];
    std::strcpy(*vector, string);
    ++size;
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& object) {
    capacity = object.capacity;
    size = object.size;
    vector = new T[capacity];
    std::copy(object.vector, object.vector + object.size, vector);
}

template<>
MyVector<char*>::MyVector(const MyVector<char*>& object) {
    capacity = object.capacity;
    size = object.size;
    vector = new char*[capacity];

    for (size_t i = 0; i < size; ++i) {
        vector[i] = new char[std::strlen(object[i]) + 1];
        std::strcpy(vector[i], object[i]);
    }

}

template<class T>
MyVector<T>::~MyVector() {
    delete[] vector;
}

template<>
MyVector<char*>::~MyVector() {
    for (size_t i = 0; i < capacity; ++i) {
        if (vector[i]) {
            delete[] vector[i];
        }
    }

    delete[] vector;
}

template<class T>
int MyVector<T>::length() {
    return size;
}

template<class T>
void MyVector<T>::pushBack(const T element) {
    if (size >= capacity) {
        resize();
    }

    vector[size++] = element;
}

template<>
void MyVector<char*>::pushBack(char* string) {
    if (size >= capacity) {
            resize();
        }

    if (vector[size]) {
        delete[] vector[size];
    }

    vector[size] = new char[std::strlen(string) + 1];

    std::strcpy(vector[size++], string);
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

template<>
void MyVector<char*>::deleteElement(const int index) {
    if (index < 0 || index >= size) {
        throw std::runtime_error("index out of boundary");
    }

    --size;

    for (size_t i = static_cast<size_t>(index); i < size; ++i) {
        delete[] vector[i];
        vector[i] = new char[std::strlen(vector[i + 1]) + 1];
        std::strcpy(vector[i], vector[i + 1]);
    }

    if (capacity > kDefaultVectorCapacity && size < (capacity / kReductionFactor)) {
        resize();
    }
}

template<class T>
int MyVector<T>::findElement(const T element) {
    for (size_t i = 0; i < size; ++i) {
        if (vector[i] == element) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

template<>
int MyVector<char*>::findElement(char* string) {
    for (size_t i = 0; i < size; ++i) {
        if (!std::strcmp(vector[i], string)) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

template<class T>
void MyVector<T>::sort() {
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

template<>
void MyVector<char*>::sort() {
    bool sorted = false;

    for (size_t i = 0; i < size && !sorted; ++i) {
        sorted = true;

        for (size_t j = 0; j < size - i - 1; ++j) {
            if (std::strcmp(vector[j], vector[j + 1]) > 0) {
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
    size = object.size;
    vector = new T[object.capacity];

    std::copy(object.vector, object.vector + object.size, vector);

    return *this;
}

template<>
MyVector<char*>& MyVector<char*>::operator=(const MyVector<char*>& object) {
    if (vector) {
        delete[] vector;
    }

    capacity = object.capacity;
    size = object.size;
    vector = new char*[object.capacity];

    for (size_t i = 0; i < size; ++i) {
        vector[i] = new char[std::strlen(object[i]) + 1];
        std::strcpy(vector[i], object[i]);
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
