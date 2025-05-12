#include "MyVector.h"

template<>
int Compare(char* first, char* second) {
    return std::strcmp(first, second);
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