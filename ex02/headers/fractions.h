#ifndef __fraction__
#define __fraction__

#include <iostream>
#include <ostream>

class Fraction {
protected:
    int numerator_;
    int denominator_;

public:
    // Defualt constructor - if not declared, C++ will create one for you
    Fraction();

    // Copy Constructor - if not declared, C++ will create one for you
    Fraction(const Fraction& f);

    Fraction(int n, int d);

    ~Fraction();

    // Fucntion call dump, pass ostream as reference!!
    void dump(std::ostream& os);
};

#endif