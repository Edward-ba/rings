#include <iostream>

#include "../headers/decimal.h"
#include "../headers/fractions.h"

int main(int argc, char* argv[]) {

    // object is created on the heap. 
    // Notice the destuctor is never called
    Fraction* pf0 = nullptr;

    {
        Fraction f0(2,3);
        pf0 = &f0;
        pf0->dump(std::cout);
    }

    // This can cause a crash since the object f0 no longer exists.
    // maybe not in debug mode
    pf0->dump(std::cout);

    Fraction *pf1 = new Fraction(3,4);
    delete pf1;

    // can crash, maybe not in debug mode
    pf1->dump(std::cout);   
}