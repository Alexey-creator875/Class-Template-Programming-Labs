#pragma once

#include "../MyVector/MyVector.h"
#include "../Term/Term.h"


class Polynomial {
 protected:
    MyVector<Term> poly;
    int degree;
};
