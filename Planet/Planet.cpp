#include "Planet.h"

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

Planet::Planet() {
    name = new char;
    *name = '\0';

    diameter = 0;
    inhabited = false;
    satellites = 0;
}

Planet::Planet(const char* name, int diameter, bool inhabited, int satellites) {
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);

    this->diameter = diameter;
    this->inhabited = inhabited;
    this->satellites = satellites;
}

Planet::Planet(const Planet& other) {
    name = new char[std::strlen(other.name) + 1];
    std::strcpy(name, other.name);
    name[std::strlen(other.name)] = '\0';
    diameter = other.diameter;
    inhabited = other.inhabited;
    satellites = other.satellites;
}

Planet::~Planet() {
    delete[] name;
}

Planet& Planet::operator=(const Planet& object) {
    if (this == &object) {
        return *this;
    }

    setName(object.name);
    diameter = object.diameter;
    inhabited = object.inhabited;
    satellites = object.satellites;

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Planet& object) {
    out << object.name << '\t' << object.diameter << '\t' << std::boolalpha << object.inhabited << '\t' << object.satellites << '\n';
    return out;
}

std::ifstream& operator>>(std::ifstream& fin, Planet& object) {
    char name[kDefaultNameSize];
    fin >> name;
    object.setName(name);
    fin >> object.diameter >> object.inhabited >> object.satellites;
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Planet& object) {
    fout << object.name << '\t' << object.diameter << '\t' << object.inhabited << '\t' << object.satellites << '\n';
    return fout;
}

void Planet::setName(const char* name) {
    delete[] this->name;
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
    this->name[std::strlen(name)] = '\0';
}

void Planet::setDiameter(int diameter) {
    this->diameter = diameter;
}

void Planet::setInhabited(bool inhabited) {
    this->inhabited = inhabited;
}

void Planet::setSatellites(int satellites) {
    this->satellites = satellites;
}

char* Planet::getName() {
    return name;
}

int Planet::getDiameter() {
    return diameter;
}

bool Planet::getInhabited() {
    return inhabited;
}

int Planet::getSatellites() {
    return satellites;
}

int Planet::readArrayFromFile(Planet*& array, size_t& size, const char* fileName) {
    std::ifstream file(fileName);

    if (!file) {
        return -1;
    }

    if (array) {
        delete[] array;
    }

    file >> size;
    array = new Planet[size];

    for (size_t i = 0; i < size; ++i) {
        file >> array[i];
    }

    file.close();
    return 0;
}

int Planet::saveArrayToFile(Planet* array, const size_t size, const char* fileName) {
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

int Planet::sortArrayByDiameter(Planet* array, const size_t size) {
    if (!array) {
        return -1;
    }

    if (size < kMinArraySize) {
        return 0;
    }

    Planet pivot = array[0];
    // int pivot = array[0].getDiameter();
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
        Planet::sortArrayByDiameter(array + kUnit, size - kUnit);
        return 0;
    }

    Planet::sortArrayByDiameter(array, leftPointer);
    Planet::sortArrayByDiameter(array + rightPointer, size - rightPointer);
    return 0;
}

int Planet::pushBack(Planet*& array, size_t& size, const Planet& item) {
    if (!array) {
        return -1;
    }

    Planet* newArray = new Planet[size + 1];

    for (size_t i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }

    newArray[size++] = item;
    delete[] array;
    array = newArray;

    return 0;
}

size_t Planet::findPlanetByName(Planet* array, const size_t size, const char* name, bool& validIndex) {
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

int Planet::removeFromArray(Planet*& array, size_t& size, const size_t removeIndex) {
    if (!array) {
        return -1;
    }

    for (size_t i = removeIndex; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }

    --size;

    return 0;

    // Planet* newArray = new Planet[size - 1];
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

bool operator<(const Planet& left, const Planet& right) {
    return left.diameter < right.diameter;
}

bool operator>=(const Planet& left, const Planet& right) {
    return right < left;
}

bool operator==(const Planet& left, const char* string) {
    return (!std::strcmp(left.name, string));
}
