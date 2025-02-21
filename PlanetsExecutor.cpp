#include "PlanetsExecutor.h"
#include "Planet/Planet.h"

#include <cstddef>
#include <iostream>

namespace PlanetsExecutor {
void ReadDataBaseFromFile(Planet::Planet*& dataBase, size_t& size) {
    
}

void RunApplication() {
    char continueExecution = 'y';

    Planet::Planet* dataBase = nullptr;
    size_t size = 0;

    while (continueExecution == 'y') {
        int action = 0;

        //print menu()

        std::cin >> action;

        switch (static_cast<Action>(action)) {
            case Action::ReadDatabaseFromFile:
                ReadDataBaseFromFile(dataBase, size);
                break;
        }
    }
}
}