#ifndef __CALC_SUM__ 
#define __CALC_SUM__ 

#include <iostream>
#include <ostream>

#include "base_analysis.h"
#include "db_manger.h"

using namespace std;

// base class for all analysis
class CalcSum : public BaseAnalysis {

    const DbManager& db_;
    vector<int> data_;
    double sum_ = 0;
    size_t n_ = 0;

public:
    CalcSum(const DbManager& db, size_t n);

public:
    void init();
    void run();
    void finalize(ostream& os);
};

#endif