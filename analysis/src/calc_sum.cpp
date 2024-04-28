#include <algorithm>
#include "../include/calc_sum.h"

CalcSum::CalcSum(const DbManager& db, size_t n)
: db_(db)
, n_(n) {

}

void CalcSum::init() {
    std::cout << "Calling Sum Init" << std::endl;   

    // do db query (inner join here)
    this->data_ = this->db_.getData();  

}

void CalcSum::run() {
    std::cout << "Calling Mean Run" << std::endl; 
    
    sum_ = 0;

    for (int i = 0; i < std::min(data_.size(), n_); ++i)
        sum_ += data_[i];
}


void CalcSum::finalize(ostream& os) {
    os  << "{ \"sum\": " << sum_ 
        << ", \"n\":" << std::min(data_.size(), n_)
        <<"}";
}

