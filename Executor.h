#pragma once

#include "MechanicalEngineering/MechanicalEngineering.h"
#include "MyStack/MyStack.h"

namespace Executor {
enum class Action {
    Finish,
    PrintProductList,
    AddProduct,
    RemoveProduct,
    Clear,
};

enum class ProductType {
    Component,
    AssemblyUnit,
    Mechanism,
};

void Print(const MyStack<Product*>& container);
bool Remove(MyStack<Product*>& container, int index);
void Clear(MyStack<Product*>& container);

void AddProductToContainer(MyStack<Product*>& container);
void RemoveProductFromContainer(MyStack<Product*>& container);
void ClearContainer(MyStack<Product*>& container);

void RunApplication();
}  // namespace Executor
