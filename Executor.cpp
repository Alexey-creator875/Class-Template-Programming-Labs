#include "Executor.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "MechanicalEngineering/MechanicalEngineering.h"
#include "MyVector/MyVector.h"

namespace Executor {
void Print(const MyVector<Product*>& container) {
    std::cout << "\nContainer";

    if (container.length() == 0) {
        std::cout << " is empty\n\n";
        return;
    }

    for (size_t i = 0; i < container.length(); ++i) {
        std::cout << '\n' << i << " element:\n\n";
        container[i]->show();
    }

    std::cout << '\n';
}

void Remove(MyVector<Product*>& container, int index) {
    if ((index < 0) || (index >= container.length())) {
        throw std::runtime_error("index out of boundary");
    }

    delete container[index];
    container.deleteElement(index);

    std::cout << "\nElement is deleted sucessfully!\n";
}

void Clear(MyVector<Product*>& container) {
    for (size_t i = 0; i < container.length(); ++i) {
        delete container[static_cast<int>(i)];
    }

    int containerSize = container.length();

    for (int i = containerSize - 1; i >= 0; --i) {
        container.deleteElement(i);
    }

    std::cout << "\nContainer is cleared sucessfully!\n";
}

void RunApplication() {
    MyVector<Product*> container;

    container.pushBack(new Component(70, "Cuprum", "Bolt M12x60 GOST 7798-70", "GOST 7798-70"));
    container.pushBack(new Component(180, "Steel", "Bushing"));
    container.pushBack(new AssemblyUnit(520, "Iron", "Bearing", 4));
    container.pushBack(new AssemblyUnit(480, "Iron", "Lock", 3));
    container.pushBack(new Mechanism(270, "Steel", "Reductor", 7, 8200, "Friction reduction"));
    container.pushBack(new Mechanism(1420, "Steel", "Watch", 7, 23499, "Time tracking"));

    Print(container);

    Remove(container, 3);
    Print(container);

    Clear(container);
    Print(container);
}
}  // namespace Executor
