#include "MechanicalEngineering.h"

#include <cstddef>
#include <cstring>
#include <iostream>

namespace {
const double kDeffaultMass = 0.;
const size_t kDeffaultMaterialSize = 2;
const size_t kDeffaultNameSize = 2;

const size_t kDeffaultGOSTSize = 2;

const int kDeffaultStructuralPartsNumber = 0;

const double kDeffaultPrice = 0.;
const size_t kDeffaultAssignmentSize = 2;
}  // namespace

Product::Product() {
    std::cout << "deffault Product()\n";

    mass = kDeffaultMass;

    material = new char[kDeffaultMaterialSize]{};
    *material = '-';

    name = new char[kDeffaultNameSize]{};
    *name = '-';
}

Product::Product(double mass, const char* material, const char* name) : mass(mass) {
    std::cout << "Product()\n";

    this->material = new char[std::strlen(material) + 1];
    std::strcpy(this->material, material);

    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
}

Product::Product(const Product& object) {
    std::cout << "copy Product()\n";

    mass = object.mass;

    material = new char[std::strlen(object.material) + 1];
    std::strcpy(material, object.material);

    name = new char[std::strlen(object.name) + 1];
    std::strcpy(name, object.name);
}

Product::~Product() {
    std::cout << "~Product()\n";

    if (material) {
        delete[] material;
    }

    if (name) {
        delete[] name;
    }
}

Product& Product::operator=(const Product& object) {
    setMass(object.mass);
    setMaterial(object.material);
    setName(object.name);

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

void Product::setName(const char* name) {
    if (this->name) {
        delete[] this->name;
    }

    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
}

double Product::getMass() {
    return mass;
}

const char* Product::getMaterial() {
    return static_cast<const char*>(material);
}

const char* Product::getName() {
    return static_cast<const char*>(name);
}

Component::Component() : Product() {
    std::cout << "deffault Component()\n";

    standard = false;
    GOST = new char[kDeffaultGOSTSize];
    *GOST = '-';
}

Component::Component(double mass, const char* material, const char* name) : Product(mass, material, name) {
    std::cout << "Component()\n";

    standard = false;
    GOST = new char[kDeffaultGOSTSize];
    *GOST = '-';
}

Component::Component(double mass, const char* material, const char* name, const char* GOST) : Product(mass, material, name) {
    std::cout << "Component()\n";

    standard = true;

    this->GOST = new char[std::strlen(GOST) + 1];
    std::strcpy(this->GOST, GOST);
}

Component::Component(const Component& object) : Product(object.mass, object.material, object.name) {
    std::cout << "copy Component()\n";

    standard = object.standard;

    GOST = new char[std::strlen(object.GOST) + 1];
    std::strcpy(GOST, object.GOST);
}

Component::~Component() {
    std::cout << "~Component()\n";

    if (GOST) {
        delete[] GOST;
    }
}

Component& Component::operator=(const Component& object) {
    setMass(object.mass);
    setMaterial(object.material);
    setName(object.name);

    if (object.standard) {
        this->setGOST(object.GOST);
    }
    return *this;
}

void Component::setGOST(const char* GOST) {
    standard = true;

    if (this->GOST) {
        delete[] this->GOST;
    }

    this->GOST = new char[std::strlen(GOST) + 1];
    std::strcpy(this->GOST, GOST);
}

bool Component::isStandart() {
    return standard;
}

const char* Component::getGOST() {
    return static_cast<const char*>(GOST);
}

void Component::show() {
    if (standard) {
        std::cout << "Standard ";
    } else {
        std::cout << "Non-standard ";
    }

    std::cout << "Component\n";

    std::cout << "Name: " << name << '\n';
    std::cout << "GOST: " << GOST << '\n';
    std::cout << "Mass: " << mass << " grams\n";
    std::cout << "Material: " << material << '\n';
}

AssemblyUnit::AssemblyUnit() : Product(), structuralPartsNumber(kDeffaultStructuralPartsNumber) {
    std::cout << "deffault AssemblyUnit()\n";
}

AssemblyUnit::AssemblyUnit(double mass, const char* material , const char* name)
    : Product(mass, material, name), structuralPartsNumber(kDeffaultStructuralPartsNumber) {
    std::cout << "AssemblyUnit()\n";
}

AssemblyUnit::AssemblyUnit(double mass, const char* material, const char* name, int structuralPartsNumber)
    : Product(mass, material, name), structuralPartsNumber(structuralPartsNumber) {
    std::cout << "AssemblyUnit()\n";
}

AssemblyUnit::AssemblyUnit(const AssemblyUnit& object)
    : Product(object.mass, object.material, object.name), structuralPartsNumber(object.structuralPartsNumber) {
    std::cout << "copy AssemblyUnit()\n";
}

AssemblyUnit::~AssemblyUnit() {
    std::cout << "~AssemblyUnit()\n";
}

AssemblyUnit& AssemblyUnit::operator=(const AssemblyUnit& object) {
    setMass(object.mass);
    setMaterial(object.material);
    setName(object.name);
    setStructuralPartsNumber(object.structuralPartsNumber);

    return *this;
}

void AssemblyUnit::setStructuralPartsNumber(int number) {
    structuralPartsNumber = number;
}

int AssemblyUnit::getStructuralPartsNumber() {
    return structuralPartsNumber;
}

void AssemblyUnit::show() {
    std::cout << "Assembly unit\n";
    std::cout << "Name: " << name << '\n';
    std::cout << "Mass: " << mass << '\n';
    std::cout << "Material: " << material << '\n';
    std::cout << "Number of structural parts: " << structuralPartsNumber << '\n';
}

Mechanism::Mechanism() : AssemblyUnit() {
    std::cout << "deffault Mechanism()\n";

    price = kDeffaultPrice;

    assignment = new char[kDeffaultAssignmentSize]{};
    *assignment = '-';
}

Mechanism::Mechanism(double mass, const char* material , const char* name, int structuralPartsNumber) : AssemblyUnit(mass, material, name, structuralPartsNumber) {
    std::cout << "Mechanism()\n";

    price = kDeffaultPrice;

    assignment = new char[kDeffaultAssignmentSize]{};
    *assignment = '-';
}

Mechanism::Mechanism(double mass, const char* material , const char* name, int structuralPartsNumber, double price, const char* assignment) : AssemblyUnit(mass, material, name, structuralPartsNumber) {
    std::cout << "Mechanism()\n";

    this->price = price;

    this->assignment = new char[std::strlen(assignment) + 1]{};
    std::strcpy(this->assignment, assignment);
}

Mechanism::Mechanism(const Mechanism& object) : AssemblyUnit(object.mass, object.material, object.name, object.structuralPartsNumber) {
    std::cout << "copy Mechanism()\n";

    price = object.price;

    assignment = new char[std::strlen(object.assignment) + 1]{};
    std::strcpy(assignment, object.assignment);
}

Mechanism::~Mechanism() {
    std::cout << "~Mechanism()\n";

    if (assignment) {
        delete[] assignment;
    }
}

void Mechanism::setPrice(double price) {
    this->price = price;
}

void Mechanism::setAssignment(const char* assignment) {
    if (assignment) {
        delete[] this->assignment;
    }

    this->assignment = new char[std::strlen(assignment) + 1];
    std::strcpy(this->assignment, assignment);
}

double Mechanism::getPrice() {
    return price;
}

const char* Mechanism::getAssignment() {
    return static_cast<const char*>(assignment);
}

Mechanism& Mechanism::operator=(const Mechanism& object) {
    setMass(object.mass);
    setMaterial(object.material);
    setName(object.name);
    setStructuralPartsNumber(object.structuralPartsNumber);
    setPrice(object.price);
    setAssignment(object.assignment);

    return *this;
}

void Mechanism::show() {
    std::cout << "Mechanism\n";
    std::cout << "Name: " << name << '\n';
    std::cout << "Mass: " << mass << '\n';
    std::cout << "Material: " << material << '\n';
    std::cout << "Number of structural parts: " << structuralPartsNumber << '\n';
    std::cout << "Price: " << price << " rubles\n";
    std::cout << "Assignment: " << assignment << '\n';
}
