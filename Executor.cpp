#include "Executor.h"

#include "MyVector/MyVector.h"
#include "MechanicalEngineering/MechanicalEngineering.h"

#include <cstddef>
#include <iostream>

namespace Executor {
void Print(const MyVector<Product*>& container) {
    std::cout << "\nContainer\n";

    for (size_t i = 0; i < container.length(); ++i) {
        std::cout << '\n' << i << " element:\n\n";
        container[i]->show();
    }

    std::cout << '\n';
}

void RunApplication() {
    MyVector<Product*> container;

    Component bolt(140, "Cuprum", "Bolt M12x60 GOST 7798-70", "GOST 7798-70");
    AssemblyUnit bearing(520, "Iron", "Bearing", 4);
    Mechanism reductor(270, "Steel", "Reductor", 7, 8200, "Friction reduction");

    container.pushBack(&bolt);
    container.pushBack(&bearing);
    container.pushBack(&reductor);

    Print(container);
}
}  // namespace Executor
