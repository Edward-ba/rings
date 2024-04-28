#ifndef __DB_MANAGER__ 
#define __DB_MANAGER__ 

#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

class DbManager {

    vector<int> data_= {1, 2, 3, 4, 5, 6, 7, 8, 9};

public:
    const vector<int>& getData() const { return data_;}

    vector<int> returnCopyGetDataNotGreat() { 
        vector<int> data= {1, 2, 3, 4, 5, 6, 7, 8, 9};    
        return data;
    }

    // const vector<int>& returnReferenceLocalVariableBadGetDataWillCrash() { 
    //     vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};    
    //     return data;
    // }
};

#endif