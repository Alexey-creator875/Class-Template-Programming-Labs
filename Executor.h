#pragma once

#include "MyVector/MyVector.h"
#include "MechanicalEngineering/MechanicalEngineering.h"

namespace Executor {
void Print(const MyVector<Product*>& container);
void Remove();
void Clear();

void RunApplication();
}  // namespace Executor
