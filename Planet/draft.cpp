
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace {
const size_t kMinArraySize = 1;
const size_t kUnit = 1;

void QuickSort(int* array, size_t size) {
    if (!array) {
        throw std::runtime_error("invalid array");
    }

    if (size <= kMinArraySize) {
        return;
    }

    int pivot = array[0];

    size_t leftPointer = 0;
    size_t rightPointer = size - kUnit;

    bool sorted = true;

    while (leftPointer != rightPointer) {
        while (leftPointer != rightPointer && array[leftPointer] < pivot) {
            ++leftPointer;
        }

        while (leftPointer != rightPointer && array[rightPointer] >= pivot) {
            --rightPointer;
        }

        if (leftPointer != rightPointer) {
            std::swap(array[leftPointer], array[rightPointer]);
            sorted = false;
        }
    }

    if (sorted) {
        QuickSort(array + kUnit, size - kUnit);
        return;
    }

    QuickSort(array, leftPointer);
    QuickSort(array + rightPointer, size - rightPointer);
}
}  // namespace

int main(int, char**) {
    // size_t size = 9;
    // int* array = new int[size];
    // array[0] = 2;
    // array[1] = 4;
    // array[2] = 5;
    // array[3] = 3;
    // array[4] = 9;
    // array[5] = 8;
    // array[6] = 7;
    // array[7] = 6;
    // array[8] = 1;

    size_t size = 4;
    int* array = new int[size];
    array[0] = 5;
    array[1] = 8;
    array[2] = 7;
    array[3] = 6;

    QuickSort(array, size);

    for (size_t i = 0; i < size; ++i) {
        std::cout << array[i] << '\n';
    }

    delete[] array;
    return 0;
}
