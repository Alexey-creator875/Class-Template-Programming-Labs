#include "MechanicalEngineering.h"

#include <cstddef>
#include <cstring>
#include <iostream>

namespace {
const double kDeffaultMass = 0.;
const size_t kDeffaultMaterialSize = 2;
}  // namespace

Product::Product() {
    std::cout << "deffault Product()\n";

    mass = kDeffaultMass;
    material = new char[kDeffaultMaterialSize]{};
    *material = '-';
}

Product::Product(double mass, const char* material) : mass(mass) {
    std::cout << "Product()\n";

    this->material = new char[std::strlen(material) + 1];
    std::strcpy(this->material, material);
}

Product::Product(const Product& object) {
    std::cout << "copy Product()\n";

    mass = object.mass;
    material = new char[std::strlen(object.material) + 1];
    std::strcpy(material, object.material);
}

Product::~Product() {
    std::cout << "~Product()\n";

    if (material) {
        delete[] material;
    }
}

Product& Product::operator=(const Product& object) {
    mass = object.mass;

    if (material) {
        delete[] material;
    }

    material = new char[std::strlen(object.material) + 1];
    std::strcpy(material, object.material);

    return *this;
}

void Product::setMass(double mass) {
    this->mass = mass;
}

void Product::setMaterial(const char* material) {
    if (this->material) {
        delete[] this->material;
    }

    this->material = new char[std::strlen(material) + 1];
    std::strcpy(this->material, material);
}

double Product::getMass() {
    return mass;
}

const char* Product::getMaterial() {
    return static_cast<const char*>(material);
}

void Product::show() {
    std::cout << "Mass: " << mass << '\n';
    std::cout << "Material: " << material << '\n';
}
