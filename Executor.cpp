#include "Executor.h"

#include "MySet/MySet.h"

namespace Executor {
void RunApplication() {
    MySet<int> set1;
    set1.append(1);
    set1.append(4);
    set1.append(5);
    set1.append(6);
    
    std::cout << "First set:\n";
    std::cout << set1 << "\n\n";

    set1.remove(4);
    set1.remove(8);

    std::cout << "New first set (removed 4 and 8):\n";
    std::cout << set1 << "\n\n";

    set1.append(4);

    std::cout << "Retracted first set:\n";
    std::cout << set1 << "\n\n";

    MySet<int> set2;
    set2.append(1);
    set2.append(2);
    set2.append(3);
    set2.append(4);

    std::cout << "Second set:\n";
    std::cout << set2 << "\n\n";

    MySet<int> set3 = set1;

    std::cout << "Third set (based on first one):\n";
    std::cout << set3 << "\n\n";

    std::cout << "Set operations\n"; 

    std::cout << set1 << " + " << set2 << " => " << set1 + set2 << '\n';
    std::cout << set1 << " - " << set2 << " => " << set1 - set2 << '\n';
    std::cout << set1 << " * " << set2 << " => " << set1 * set2 << '\n';
    std::cout << set1 << " == " << set2 << " => " << std::boolalpha << (set1 == set2) << '\n';
    std::cout << set1 << " == " << set3 << " => " << (set1 == set3) << '\n';

    std::cout << '\n';
}
}