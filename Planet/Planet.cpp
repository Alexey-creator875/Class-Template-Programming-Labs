#include "Planet.h"

#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
const size_t kBufferSize = 100;
const size_t kNameSize = 20;
}  // namespace

namespace Planet {
Planet::Planet() {
    name = new char[kNameSize];
    *name = '\0';

    diameter = 0;
    inhabited = false;
    satellites = 0;
}

Planet::Planet(char* name, int diameter, bool inhabited, int satellites) {
    if (diameter < 0) {
        throw std::runtime_error("invalid diameter value!");
    }

    if (satellites < 0) {
        throw std::runtime_error("invalid satellites value!");
    }

    name = new char[kNameSize];
    std::strcpy(this->name, name);

    this->diameter = static_cast<size_t>(diameter);
    this->inhabited = inhabited;
    this->satellites = static_cast<size_t>(satellites);
}

void Planet::PrintPlanetParameters() {
    std::cout << name << '\t' << diameter << '\t' << inhabited << '\t' << satellites << '\n';
}

Planet::~Planet() {
    delete[] name;
}
}  // namespace Planet
