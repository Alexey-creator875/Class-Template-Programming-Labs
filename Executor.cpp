#include "Executor.h"

#include "MySet/MySet.h"
#include "MyVector/MyVector.h"

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

    MyVector<const char*> v("Hello!");
    v.pushBack("Привет!");
    v.pushBack("Привет!");
    v.pushBack("Привет!");
    v.pushBack("Привет!");
    v.pushBack("Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    v.pushBack("Привет!");
    v.pushBack("Привет!");
    v.pushBack("Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    MyVector<const char*> v1 = v;
    std::cout << "Вектор v1: " << v1 << std::endl;
    for (int i = 0; i < v1.length(); i++)
        v1.deleteElement(0);
    std::cout << "Вектор v1: " << v1 << std::endl;
    MySet<const char*> s("Yes"), s1, s2;
    s.append("Привет!");
    s.append("No");
    const char *str = "Hello!";
    s.append(str);
    std::cout << "Множество s: " << s << std::endl;
    s1.append("Cat");
    s1.append("No");
    s1.append("Привет!");
    std::cout << "Множество s1: " << s1 << std::endl;
    s2 = s1 - s;
    std::cout << "Множество s2=s1-s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s - s1;
    std::cout << "Множество s2=s-s1: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 + s;
    std::cout << "Множество s2=s1+s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 * s;
    std::cout << "Множество s2=s1*s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    MySet<const char*> s3 = s2;
    std::cout << "Множество s3=s2: " << s3 << std::endl;
    if (s3 == s2)
        std::cout << "Множество s3=s2\n";
    else
        std::cout << "Множество s3!=s2\n";
    if (s3 == s1)
        std::cout << "Множество s3=s1\n";
    else
        std::cout << "Множество s3!=s1\n";
    if (s1 == s3)
        std::cout << "Множество s1=s3\n";
    else
        std::cout << "Множество s1!=s3\n";
}
}
