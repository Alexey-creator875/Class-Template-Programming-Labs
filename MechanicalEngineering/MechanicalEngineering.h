#pragma once

class Product {
 protected:
    double mass;
    char* material;
    char* name;

 public:
    Product();
    Product(double mass, const char* material , const char* name);
    Product(const Product& object);

    ~Product();

    void setMass(double mass);
    void setMaterial(const char* material);
    void setName(const char* name);

    double getMass();
    const char* getMaterial();
    const char* getName();

    Product& operator=(const Product& object);

    void show();
};

class Component : public Product {
 protected:
    bool standard;
    char* GOST;
 
 public:
    Component();
    Component(double mass, const char* material , const char* name);
    Component(double mass, const char* material , const char* name, const char* GOST);
    Component(const Component& object);

    ~Component();

    void setGOST(const char* GOST);

    bool isStandart();
    const char* getGOST();

    Component& operator=(const Component& object);

    void show();
};

class AssemblyUnit : public Product {
 protected:
    int structuralPartsNumber;

 public:
    AssemblyUnit();
    AssemblyUnit(double mass, const char* material , const char* name);
    AssemblyUnit(double mass, const char* material , const char* name, int structuralPartsNumber);
    AssemblyUnit(const AssemblyUnit& object);

    ~AssemblyUnit();

    void setStructuralPartsNumber(int number);

    int getStructuralPartsNumber();

    AssemblyUnit& operator=(const AssemblyUnit& object);

    void show();
};

class Mechanism : public AssemblyUnit {
 protected:
    double price;
    char* assignment;

 public:
    Mechanism();
    Mechanism(double mass, const char* material , const char* name, int structuralPartsNumber);
    Mechanism(double mass, const char* material , const char* name, int structuralPartsNumber, double price, const char* assignment);
    Mechanism(const Mechanism& object);

    ~Mechanism();

    void setPrice(double price);
    void setAssignment(const char* assignment);

    double getPrice();
    const char* getAssignment();

    Mechanism& operator=(const Mechanism& object);

    void show();
};
