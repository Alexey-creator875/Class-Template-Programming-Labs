#include "Executor.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "MechanicalEngineering/MechanicalEngineering.h"
#include "MyStack/MyStack.h"

namespace {
const size_t kBufferSize = 40;

void AddComponentToConteiner(MyStack<Product*>& container) {
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

        container.push(new Component(mass, material, name, GOST));
        return;
    }

    container.push(new Component(mass, material, name));
}

void AddAssemblyUnitToConteiner(MyStack<Product*>& container) {
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

    container.push(new AssemblyUnit(mass, material, name, structuralPartsNumber));
}

void AddMechanismToConteiner(MyStack<Product*>& container) {
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

    container.push(new Mechanism(mass, material, name, structuralPartsNumber, price, assignment));
}
}  // namespace

namespace Executor {
void Print(const MyStack<Product*>& container) {
    if (container.empty()) {
        std::cout << "\nContainer is empty\n\n";
        return;
    }

    std::cout << "\nContainer";

    ListNode<Product*, MyStack<Product*>>* temp = container.getTop();

    size_t count = 0;

    while (temp) {
        std::cout << '\n' << count << " element:\n\n";
        temp->getData()->show();
        temp = temp->getNext();
        ++count;
    }

    std::cout << '\n';
}

bool Remove(MyStack<Product*>& container, int index) {

    ListNode<Product*, MyStack<Product*>>* currentNode = container.getTop();
    ListNode<Product*, MyStack<Product*>>* previousNode = nullptr;

    size_t stackIndex = 0;

    while (currentNode && stackIndex < index) {
        previousNode = currentNode;
        currentNode = currentNode->getNext();
        ++stackIndex;
    }

    previousNode->setNext(currentNode->getNext());

    if(currentNode->getData()) {
        delete currentNode->getData();
    }
    
    if (currentNode) {
        delete currentNode;
    }

    return true;
}

void Clear(MyStack<Product*>& container) {
    if (container.empty()) {
        return;
    }

    while (!container.empty()) {
        delete container.getTop()->getData();
        container.pop();
    }
}

void AddProductToContainer(MyStack<Product*>& container) {
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

void RemoveProductFromContainer(MyStack<Product*>& container) {
    int index = 0;
    std::cout << "Enter index of product:\n";
    std::cin >> index;

    if (!Remove(container, index)) {
        std::cout << "Failed to delete product";
        return;
    }

    std::cout << "\nElement is deleted sucessfully!\n";
}

void ClearContainer(MyStack<Product*>& container) {
    Clear(container);
    std::cout << "\nContainer is cleared sucessfully!\n";
}

void RunApplication() {
    MyStack<Product*> container;

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
