#pragma once

#include <cstddef>
#include <fstream>

namespace Planet {
class Planet {
 private:
    char* name;
    size_t diameter;
    bool inhabited;
    size_t satellites;

 public:
    Planet();
    Planet(char* name, int diameter, bool inhabited, int satellites);
    void PrintPlanetParameters();
    void ReadPlanetFromStdIn(std::ifstream& inputFile);
    ~Planet();
};
}  // namespace Planet
