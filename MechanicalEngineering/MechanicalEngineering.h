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

    Product& operator=(const Product& object);

    void setMass(double mass);
    void setMaterial(const char* material);
    void setName(const char* name);

    double getMass();
    const char* getMaterial();
    const char* getName();

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

    Component& operator=(const Component& object);

    void setGOST(const char* GOST);

    bool isStandart();
    const char* getGOST();

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

    AssemblyUnit& operator=(const AssemblyUnit& object);

    void setStructuralPartsNumber(int number);

    int getStructuralPartsNumber();

    void show();
};