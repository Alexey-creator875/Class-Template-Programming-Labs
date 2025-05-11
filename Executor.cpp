#include "Executor.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "MechanicalEngineering/MechanicalEngineering.h"
#include "MyVector/MyVector.h"

namespace {
const size_t kBufferSize = 40;

void AddComponentToConteiner(MyVector<Product*>& container) {
    int mass = 0;
    std::cout << "Enter mass:\n";
    std::cin >> mass;

    char material[kBufferSize]{};
    std::cout << "Enter material:\n";
    std::cin.getline(material, kBufferSize, '\n');
    std::cin.getline(material, kBufferSize, '\n');

    char name[kBufferSize]{};
    std::cout << "Enter name:\n";
    std::cin.getline(name, kBufferSize, '\n');

    char standard = 'n';
    std::cout << "Is product standard? (y/n)\n";
    std::cin >> standard;

    if (standard == 'y') {
        char GOST[kBufferSize]{};
        std::cout << "Enter GOST:\n";
        std::cin.getline(GOST, kBufferSize, '\n');
        std::cin.getline(GOST, kBufferSize, '\n');

        container.pushBack(new Component(mass, material, name, GOST));
        return;
    }

    container.pushBack(new Component(mass, material, name));
}

void AddAssemblyUnitToConteiner(MyVector<Product*>& container) {
    int mass = 0;
    std::cout << "Enter mass:\n";
    std::cin >> mass;

    char material[kBufferSize]{};
    std::cout << "Enter material:\n";
    std::cin.getline(material, kBufferSize, '\n');
    std::cin.getline(material, kBufferSize, '\n');

    char name[kBufferSize]{};
    std::cout << "Enter name:\n";
    std::cin.getline(name, kBufferSize, '\n');

    int structuralPartsNumber = 0;
    std::cout << "Enter number of structural parts:\n";
    std::cin >> structuralPartsNumber;

    container.pushBack(new AssemblyUnit(mass, material, name, structuralPartsNumber));
}

void AddMechanismToConteiner(MyVector<Product*>& container) {
    int mass = 0;
    std::cout << "Enter mass:\n";
    std::cin >> mass;

    char material[kBufferSize]{};
    std::cout << "Enter material:\n";
    std::cin.getline(material, kBufferSize, '\n');
    std::cin.getline(material, kBufferSize, '\n');

    char name[kBufferSize]{};
    std::cout << "Enter name:\n";
    std::cin.getline(name, kBufferSize, '\n');

    int structuralPartsNumber = 0;
    std::cout << "Enter number of structural parts:\n";
    std::cin >> structuralPartsNumber;

    double price = 0.;
    std::cout << "Enter price:\n";
    std::cin >> price;

    char assignment[kBufferSize]{};
    std::cout << "Enter assignment:\n";
    std::cin.getline(assignment, kBufferSize, '\n');
    std::cin.getline(assignment, kBufferSize, '\n');

    container.pushBack(new Mechanism(mass, material, name, structuralPartsNumber, price, assignment));
}
}  // namespace

namespace Executor {
void Print(const MyVector<Product*>& container) {
    if (container.length() == 0) {
        std::cout << "\nContainer is empty\n\n";
        return;
    }

    std::cout << "\nContainer";

    for (size_t i = 0; i < container.length(); ++i) {
        std::cout << '\n' << i << " element:\n\n";
        container[i]->show();
    }

    std::cout << '\n';
}

bool Remove(MyVector<Product*>& container, int index) {
    if ((index < 0) || (index >= container.length())) {
        return false;
    }

    delete container[index];
    container.deleteElement(index);

    return true;
}

void Clear(MyVector<Product*>& container) {
    if (container.length() == 0) {
        return;
    }

    for (size_t i = 0; i < container.length(); ++i) {
        delete container[static_cast<int>(i)];
    }

    int containerSize = container.length();

    for (int i = containerSize - 1; i >= 0; --i) {
        container.deleteElement(i);
    }
}

void AddProductToContainer(MyVector<Product*>& container) {
    int productType = 0;

    std::cout << '\n'
              << "Enter '0' to add Component\n"
              << "Enter '1' to add AssemblyUnit\n"
              << "Enter '2' to add Mechanism\n";

    std::cin >> productType;

    switch (static_cast<ProductType>(productType)) {
        case ProductType::Component:
            AddComponentToConteiner(container);
            break;
        case ProductType::AssemblyUnit:
            AddAssemblyUnitToConteiner(container);
            break;
        case ProductType::Mechanism:
            AddMechanismToConteiner(container);
            break;
    }
}

void RemoveProductFromContainer(MyVector<Product*>& container) {
    int index = 0;
    std::cout << "Enter index of product:\n";
    std::cin >> index;

    if ((index < 0) || (index >= container.length())) {
        std::cout << "invalid index\n";
        return;
    }

    if (!Remove(container, index)) {
        std::cout << "Failed to delete product";
        return;
    }

    std::cout << "\nElement is deleted sucessfully!\n";
}

void ClearContainer(MyVector<Product*>& container) {
    Clear(container);
    std::cout << "\nContainer is cleared sucessfully!\n";
}

void RunApplication() {
    MyVector<Product*> container;

    bool continueExecution = true;

    while (continueExecution) {
        int action = 0;

        std::cout << '\n'
                  << "Enter '1' to print list of products\n"
                  << "Enter '2' to add product to the list\n"
                  << "Enter '3' to remove product from the list\n"
                  << "Enter '4' to clear list of products\n"
                  << "Enter '0' to finish\n";

        std::cin >> action;

        switch (static_cast<Action>(action)) {
            case Action::Finish:
                continueExecution = false;
                break;
            case Action::PrintProductList:
                Print(container);
                break;
            case Action::AddProduct:
                AddProductToContainer(container);
                break;
            case Action::RemoveProduct:
                RemoveProductFromContainer(container);
                break;
            case Action::Clear:
                ClearContainer(container);
                break;
            default:
                std::cout << "invalid command! Try againg.\n";
                break;
        }
    }

    Clear(container);
}
}  // namespace Executor
