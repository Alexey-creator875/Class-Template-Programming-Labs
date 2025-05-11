#pragma once

#include "MechanicalEngineering/MechanicalEngineering.h"
#include "MyVector/MyVector.h"

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

void Print(const MyVector<Product*>& container);
bool Remove(MyVector<Product*>& container, int index);
void Clear(MyVector<Product*>& container);

void AddProductToContainer(MyVector<Product*>& container);
void RemoveProductFromContainer(MyVector<Product*>& container);
void ClearContainer(MyVector<Product*>& container);

void RunApplication();
}  // namespace Executor
