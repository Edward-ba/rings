#ifndef __CalcMean__ 
#define __CalcMean__ 

#include <iostream>
#include <ostream>

#include "base_analysis.h"
#include "db_manger.h"
using namespace std;

// base class for all analysis
class CalcMean : public BaseAnalysis {

    const DbManager& db_;
    vector<int> data_;
    double mean_ = 0;

public:
    CalcMean(const DbManager& db);
//    ~CalcMean() {};

    void init(); 
    void run();
    void finalize(ostream& os);
};

#endif