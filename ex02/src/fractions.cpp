#include "../headers/fractions.h"
#include "../headers/decimal.h"

Fraction::Fraction() 
: numerator_(0)         // These are called initalized lists
, denominator_(0){      // member variables are initialized in the order they were defined
                        // not they are initialzied (standard interview/test question)                            

    // it's better do via initializer list instead of doing this
    // numerator_ = 0;
    
    std::cout << "Default::Constructor " 
        << numerator_ << "/"<< denominator_
        << std::endl;
}

// Definition of copy constructor - again this is auto created for if you don't
// Define/declare one yourself
Fraction::Fraction(const Fraction& f) 
: numerator_(f.numerator_)
, denominator_(f.denominator_) {
    std::cout << "Copy::Constructor " 
        << numerator_ << "/"<< denominator_
        << std::endl;
}


Fraction::Fraction(int n, int d) 
: numerator_(n)
, denominator_(d){
    std::cout << "Parameterized Constructor " 
        << numerator_ << "/"<< denominator_
        << std::endl;
}

// Destructor
Fraction::~Fraction() {
    std::cout << "Destructor " 
        << numerator_ << "/"<< denominator_
        << std::endl;
}

void Fraction::dump(std::ostream& os) {
    std::cout << "Calling dump " 
        << this->numerator_ << "/"<< this->denominator_
        << std::endl;
}

