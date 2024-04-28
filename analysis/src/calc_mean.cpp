#include "../include/calc_mean.h"

CalcMean::CalcMean(const DbManager& db)
: db_(db) {

}

void CalcMean::init() {
    std::cout << "Calling Mean Init" << std::endl; 
    this->data_ = this->db_.getData();  

}

void CalcMean::run() {

    std::cout << "Calling Mean Run" << std::endl; 
    
    mean_ = 0;
    for (auto x : data_)
        mean_ += x;
    mean_ = mean_ / data_.size();
}


void CalcMean::finalize(ostream& os) {
    os << "{ \"mean\": " << mean_ <<"}";
}

