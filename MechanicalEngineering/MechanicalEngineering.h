#pragma once

class Product {
 protected:
    double mass;
    char* material;

 public:
    Product();
    Product(double mass, const char* material);
    Product(const Product& object);

    ~Product();

    Product& operator=(const Product& object);

    void setMass(double mass);
    void setMaterial(const char* material);

    double getMass();
    const char* getMaterial();

    void show();
};
