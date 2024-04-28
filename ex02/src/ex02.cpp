#include <iostream>

#include "../headers/fractions.h"
#include "../headers/decimal.h"

using namespace std;

int main() {

    Decimal d0(1,2);
    d0.dump(cout);

    Decimal d1(2,3);
    d1.add_to(d0);
    d1.dump(cout);

    d1.add_back(d0);
    d0.dump(cout);
    cout << "------\n";


    Decimal *pD0 = nullptr;
    Decimal *pD1 = nullptr;

    {
        pD0 = new Decimal(5,6);
    }
    pD1 = pD0;
    pD1->dump(cout);

    delete pD0;
    // at this point pD0 and pD1 point to nothing,
    // you cannnot use it

    // point pD1 to the address off d1
    pD1 = &d1;

    pD1->dump(cout);


    return 0;

    cout << "Create fractions" << endl;
    Fraction f0;
    Fraction f1(2,3);   

    {
        cout << "\nCreate fractions - within scope" << endl;
        Fraction f2(4,5);
        cout << "\nDestructor calls - within scope" << endl;

    }

    cout << "\nCreate fractions - copy Constructor" << endl;
    Fraction f3(f1);
    f3.dump(cout);
    
    cout << "\nDestructor calls" << endl;
    
}