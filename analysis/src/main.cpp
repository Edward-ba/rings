#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <sstream>


#include "../include/calc_mean.h"
#include "../include/calc_sum.h"
#include "../include/db_manger.h"

using namespace std;





int main(int argc, char* argv[]) {

    DbManager db;

//    { run "calc_mean", calc_sum":3"}
//    32afafaf13314616


    list<BaseAnalysis*> analysis_lists;

    analysis_lists.push_back(new CalcMean(db));
    analysis_lists.push_back(new CalcSum(db, 3));


//  map<requests, list<BaseAnalysis*>


    for (auto& a : analysis_lists) {
        a->init();
        a->run();
    }

    std::stringstream ss;
    ss << "[";

    for (auto& a : analysis_lists) {
        a->finalize(ss);
        ss << ",";
    }
    ss << "]";


    cout << "\n" << ss.str() << endl;

    // CalcSum cs;
    // cs.init();
    // cs.run();
    // cs.finalize(cout);



}