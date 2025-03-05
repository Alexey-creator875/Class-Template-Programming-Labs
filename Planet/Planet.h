#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>

class Planet {
 private:
    char* name;
    int diameter;
    bool inhabited;
    int satellites;

 public:
    Planet();
    Planet(const char* name, int diameter, bool inhabited, int satellites);
    Planet(const Planet& other);
    ~Planet();

    Planet& operator=(const Planet& object);
    friend std::ostream& operator<<(std::ostream& out, const Planet& object);
    friend std::ifstream& operator>>(std::ifstream& fin, Planet& object);
    friend std::ofstream& operator<<(std::ofstream& fout, const Planet& object);
    friend bool operator<(const Planet& left, const Planet& right);
    friend bool operator>=(const Planet& left, const Planet& right);
    friend bool operator==(const Planet& left, const char* string);

    void setName(const char* name);
    void setDiameter(int diameter);
    void setInhabited(bool inhabited);
    void setSatellites(int satellites);

    char* getName();
    int getDiameter();
    bool getInhabited();
    int getSatellites();

    static int readArrayFromFile(Planet*& array, size_t& size, const char* fileName);
    static int saveArrayToFile(Planet* array, const size_t size, const char* fileName);
    static int sortArrayByDiameter(Planet* array, const size_t size);
    static int pushBack(Planet*& array, size_t& size, const Planet& item);
    static size_t findPlanetByName(Planet* array, const size_t size, const char* name, bool& validIndex);
    static int removeFromArray(Planet*& array, size_t& size, const size_t removeIndex);
};
