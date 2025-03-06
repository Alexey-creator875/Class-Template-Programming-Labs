#include "Person.h"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

namespace {
const size_t kDefaultNameSize = 20;
const size_t kMinArraySize = 1;
const size_t kUnit = 1;
}  // namespace

Person::Person() {
    name = new char;
    *name = '\0';

    age = 0;
    height = 0;
    weight = 0;
}

Person::Person(const char* name, int age, int height, int weight) {
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);

    this->age = age;
    this->height = height;
    this->weight = weight;
}

Person::Person(const Person& other) {
    name = new char[std::strlen(other.name) + 1];
    std::strcpy(name, other.name);
    name[std::strlen(other.name)] = '\0';
    age = other.age;
    height = other.height;
    weight = other.weight;
}

Person::~Person() {
    std::cout << name << std::endl;
    delete[] name;
}

Person& Person::operator=(const Person& object) {
    if (this == &object) {
        return *this;
    }

    setName(object.name);
    age = object.age;
    height = object.height;
    weight = object.weight;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Person& object) {
    out << object.name << '\t' << object.age << '\t' << std::boolalpha << object.height << '\t' << object.weight << '\n';
    return out;
}

std::ifstream& operator>>(std::ifstream& fin, Person& object) {
    char name[kDefaultNameSize];
    fin >> name;
    object.setName(name);
    fin >> object.age >> object.height >> object.weight;
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Person& object) {
    fout << object.name << '\t' << object.age << '\t' << object.height << '\t' << object.weight << '\n';
    return fout;
}

void Person::setName(const char* name) {
    delete[] this->name;
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
    this->name[std::strlen(name) + 1] = '\0';
}

void Person::setAge(int age) {
    this->age = age;
}

void Person::setHeight(int height) {
    this->height = height;
}

void Person::setWeight(int weight) {
    this->weight = weight;
}

char* Person::getName() {
    return name;
}

int Person::getAge() {
    return age;
}

bool Person::getHeight() {
    return height;
}

int Person::getWeight() {
    return weight;
}

int Person::readArrayFromFile(Person*& array, size_t& size, const char* fileName) {
    std::ifstream file(fileName);

    if (!file) {
        return -1;
    }

    if (array) {
        delete[] array;
    }

    file >> size;
    array = new Person[size];

    for (size_t i = 0; i < size; ++i) {
        file >> array[i];
    }

    file.close();
    return 0;
}

int Person::saveArrayToFile(Person* array, const size_t size, const char* fileName) {
    if (!array) {
        return -1;
    }

    std::ofstream file(fileName, std::ios::trunc);

    file << size << '\n';

    for (size_t i = 0; i < size; ++i) {
        file << array[i];
    }

    file.close();
    return 0;
}

int Person::sortArrayByName(Person* array, const size_t size) {
    if (!array) {
        return -1;
    }

    if (size < kMinArraySize) {
        return 0;
    }

    Person pivot = array[0];
    size_t leftPointer = 0;
    size_t rightPointer = size - kUnit;
    bool foundLessThanPivot = false;

    while (leftPointer != rightPointer) {
        while (leftPointer != rightPointer && array[leftPointer] < pivot) {
            ++leftPointer;
        }

        while (leftPointer != rightPointer && array[rightPointer] >= pivot) {
            --rightPointer;
        }

        if (leftPointer != rightPointer) {
            std::swap(array[leftPointer], array[rightPointer]);
            foundLessThanPivot = true;
        }
    }

    if (!foundLessThanPivot) {
        Person::sortArrayByName(array + kUnit, size - kUnit);
        return 0;
    }

    Person::sortArrayByName(array, leftPointer);
    Person::sortArrayByName(array + rightPointer, size - rightPointer);
    return 0;
}

int Person::pushBack(Person*& array, size_t& size, const Person& item) {
    if (!array) {
        return -1;
    }

    Person* newArray = new Person[size + 1];

    for (size_t i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }

    newArray[size++] = item;
    delete[] array;
    array = newArray;

    return 0;
}

size_t Person::findPersonByName(Person* array, const size_t size, const char* name, bool& validIndex) {
    if (!array) {
        validIndex = false;
        return 1;
    }

    validIndex = true;
    size_t searchIndex = 0;

    while (searchIndex < size) {
        if (array[searchIndex] == name) {
            return searchIndex;
        }

        ++searchIndex;
    }

    validIndex = false;
    return 0;
}

int Person::removeFromArray(Person*& array, size_t& size, const size_t removeIndex) {
    if (!array) {
        return -1;
    }

    for (size_t i = removeIndex; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }

    --size;

    return 0;

    // Person* newArray = new Person[size - 1];
    // size_t newArrayIndex = 0;

    // for (size_t i = 0; i < size; ++i) {
    //     if (i == removeIndex) {
    //         continue;
    //     }

    //     newArray[newArrayIndex++] = array[i];
    // }

    // --size;
    // delete[] array;
    // array = newArray;
    // return 0;
}

bool operator<(const Person& left, const Person& right) {
    return (std::strcmp(left.name, right.name) < 0);
}

bool operator>=(const Person& left, const Person& right) {
    return right < left;
}

bool operator==(const Person& left, const char* string) {
    return (!std::strcmp(left.name, string));
}
