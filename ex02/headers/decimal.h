#ifndef __decimal__
#define __decimal__

#include <iostream>
#include <ostream>

class Decimal {
protected:
    int real_;
    int float_;

public:
    Decimal();
    Decimal(int r, int f);

    ~Decimal();

    void change(int r, int f);

    // TODO. add the value of dec to current, Barry implement 
    // the const on the arguments say that you cannnot change the argument
    void add_to(const Decimal& dec);

    void add_back(Decimal& dec);

    bool is_lessthan(const Decimal& dec);

    // read up unary and binary operators
    // https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
    Decimal operator + (const Decimal& rhs);
    bool operator< (const Decimal& rhs);

    // The const at the end says this function cannot change the object
    void dump(std::ostream& os) const;
};

#endif