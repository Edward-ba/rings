#include "../headers/decimal.h"
#include "../headers/decimal.h"
#include "../headers/decimal.h"

#include <iostream>

Decimal::Decimal() 
: real_(0)
, float_(0){
    std::cout << "Default::Constructor " 
        << real_ << "/"<< float_
        << std::endl;
}

Decimal::Decimal(int n, int d) 
: real_(n)
, float_(d){
    std::cout << "Parameterized Constructor " 
        << real_ << "."<< float_
        << std::endl;
}

// Destructor
Decimal::~Decimal() {
    std::cout << "Destructor " 
        << real_ << "."<< float_
        << std::endl;
}


void Decimal::add_to(const Decimal& dec) {

    this->real_ += dec.real_;
    this->float_ += dec.float_;    
    //dec.dump(std::cout);
}


void Decimal::add_back(Decimal& dec) {

    dec.real_ += this->real_;
    dec.float_ += this->float_;
    
    //dec.dump(std::cout);

}


void Decimal::change(int r, int f) {
    real_ = r;
    float_ = f;
}

void Decimal::dump(std::ostream& os) const {
    std::cout << "Calling Function dump " 
        << this->real_ << "."<< this->float_
        << std::endl;
}
