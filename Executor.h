#pragma once

#include <string>

namespace Executor {
enum class Task {
    Finish,
    First,
    Second,
    Third,
    Fourth,
    Fifth,
    Sixth,
    Seventh,
    Eighth,
    Ninth,
};

class Box {
 private:
    double width;
    double height;
    double length;

 public:
    Box() : width(0), height(0), length(0) {}
    Box(double width, double height, double length) : width(width), height(height), length(length) {}

    void setWidth(double width) { this->width = width; }
    void setHeight(double height) { this->height = height; }
    void setLength(double length) { this->length = length; }

    double getWidth() { return width; }
    double getHeight() { return height; }
    double getLength() { return length; }

    friend bool operator<(const Box& first, const Box& second);
    friend bool operator==(const Box& first, const Box& second);
};

class Graduate {
    std::string name;
    double rating;

 public:
    Graduate() {
        name = "";
        rating = 0;
    }
    Graduate(std::string Name, double Rating) {
        name = Name;
        rating = Rating;
    }

    void setName(std::string name) { this->name = name; }
    void setRating(double rating) { this->rating = rating; }

    std::string getName() { return name; }
    double getRating() { return rating; }

    friend bool operator<(const Graduate& first, const Graduate& second);
    friend bool operator==(const Graduate& first, const Graduate& second);
};

void PerformFirstTask();
void PerformSecondTask();
void PerformThirdTask();
void PerformFourthTask();
void PerformFifthTask();
void PerformSixthTask();
void PerformSeventhTask();
void PerformEighthTask();
void PerformNinthTask();

void RunApplication();
}  // namespace Executor
