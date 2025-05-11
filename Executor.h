#pragma once

#include "MechanicalEngineering/MechanicalEngineering.h"
#include "MyVector/MyVector.h"

namespace Executor {
void Print(const MyVector<Product*>& container);
void Remove(MyVector<Product*>& container, int index);
void Clear(MyVector<Product*>& container);

void RunApplication();
}  // namespace Executor
