#ifndef __BASE_ANALYSIS__ 
#define __BASE_ANALYSIS__ 

#include <iostream>
#include <ostream>

using namespace std;

// base class for all analysis
class BaseAnalysis {

public:
    virtual void init() = 0;
    virtual void run() = 0;
    virtual void finalize(ostream& os) = 0;
};

#endif