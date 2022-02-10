//
// Created by ludwig on 22.11.16.
//

#include <iostream>
#include <string>
#include "Tests.h"


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// To Be Removed
//
//using namespace ClassProject;
//
//int main(int argc, char* argv[])
//{
//    Reachability reachableState;
//
//    vector<BDD_ID> x;
//    vector<BDD_ID> s;
//    vector<bool> y;
//
//    reachableState.ReachabilityInterface(2);
//    s = reachableState.getStates();
//    x.push_back(reachableState.neg(s[0]));
//    x.push_back(reachableState.neg(s[1]));
//    reachableState.setTransitionFunctions(x);
//
//    y.push_back(0);
//    y.push_back(0);
//    reachableState.setInitState(y);
//
//    reachableState.isReachable(y);
//    reachableState.print_table();
//
//    return 0;
//}
