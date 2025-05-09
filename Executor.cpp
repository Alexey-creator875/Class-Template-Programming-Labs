#include "Executor.h"

#include <iostream>

#include "Polynomial/Polynomial.h"

namespace Executor {
void RunApplication() {
    std::cout << "Terms\n\n";

    Term t1;
    Term t2(3);
    Term t3(3, 1);
    Term t4(1, 3);
    Term t5(-3, 2);

    std::cout << "t1: " << t1 << '\n';
    std::cout << "t2: " << t2 << '\n';
    std::cout << "t3: " << t3 << '\n';
    std::cout << "t4: " << t4 << '\n';
    std::cout << "t5: " << t5 << '\n';

    std::cout << "x^3 + 5x^3 = " << (Term(1, 3) + Term(5, 3)) << '\n';

    Term t6;
    std::cout << "Enter your own term:\n";
    std::cin >> t6;

    std::cout << "Your term:\n" << t6 << '\n';

    std::cout << "\nPolynomials\n\n";

    Polynomial p1;
    Polynomial p2(3);
    Polynomial p3(Term(3, 2));

    std::cout << "p1: " << p1 << '\n';
    std::cout << "p2: " << p2 << '\n';
    std::cout << "p3: " << p3 << '\n';

    Polynomial p4;
    p4 += Term(5, 5);
    p4 += Term(-4, 3);
    p4 += Term(1, 2);
    p4 += Term(0, 1);
    p4 += Term(7, 0);

    std::cout << "descending p4: " << p4 << '\n';
    p4.changeOrder();
    std::cout << "ascending p4: " << p4 << '\n';
    p4.changeOrder();

    Polynomial p5;
    p5 += Term(1, 1);
    p5 += Term(3, 0);

    std::cout << "p5: " << p5 << '\n';

    Polynomial p6;
    p6 += Term(1, 1);
    p6 += Term(-2, 0);

    std::cout << "p6: " << p6 << '\n';

    std::cout << "p5 + p6 = " << (p5 + p6) << '\n';
    std::cout << "p5 * p6 = " << (p5 * p6) << '\n';

    p5 += p6;
    std::cout << "p5 += p6; p5: " << p5 << '\n';

    p5 *= p6;
    std::cout << "p5 *= p6; p5: " << p5 << '\n';

    Polynomial p7;

    std::cout << "Enter your own polynomial:\n";
    std::cin >> p7;

    std::cout << "Your polynomial:\n" << p7 << '\n';
}
}  // namespace Executor
