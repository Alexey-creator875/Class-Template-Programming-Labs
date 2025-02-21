#pragma once

#include "Planet/Planet.h"

namespace PlanetsExecutor {
enum class Action {
    Exit,
    ReadDatabaseFromFile,

};

void ReadDataBaseFromFile(Planet::Planet*& dataBase, size_t& size);

void RunApplication();
}