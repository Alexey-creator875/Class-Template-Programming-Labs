#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>

class Person {
 private:
    char* name;
    int age;
    int height;
    int weight;

 public:
    Person();
    Person(const char* name, int age, int height, int weight);
    Person(const Person& other);
    ~Person();

    Person& operator=(const Person& object);
    friend std::ostream& operator<<(std::ostream& out, const Person& object);
    friend std::ifstream& operator>>(std::ifstream& fin, Person& object);
    friend std::ofstream& operator<<(std::ofstream& fout, const Person& object);
    friend bool operator<(const Person& left, const Person& right);
    friend bool operator>=(const Person& left, const Person& right);
    friend bool operator==(const Person& left, const char* string);

    void setName(const char* name);
    void setAge(int age);
    void setHeight(int height);
    void setWeight(int weight);

    char* getName();
    int getAge();
    bool getHeight();
    int getWeight();

    static int readArrayFromFile(Person*& array, size_t& size, const char* fileName);
    static int saveArrayToFile(Person* array, const size_t size, const char* fileName);
    static int sortArrayByName(Person* array, const size_t size);
    static int pushBack(Person*& array, size_t& size, const Person& item);
    static size_t findPersonByName(Person* array, const size_t size, const char* name, bool& validIndex);
    static int removeFromArray(Person*& array, size_t& size, const size_t removeIndex);
};
