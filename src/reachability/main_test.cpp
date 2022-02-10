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
//    Manager MyManager;
//    bool r;
//    vector<BDD_ID> x,s;
//    vector<bool> y,z;
//
//    MyManager.ReachabilityInterface(2);
//    s = MyManager.getStates();
//    x={MyManager.neg(s[0]),MyManager.neg(s[1]),};
//    MyManager.setTransitionFunctions(x);
//
//    y= {0,0};
//    MyManager.setInitState(y);
//
////    z.push_back(0);
//    z= {1,1};
//    r = MyManager.isReachable(z);
//    cout<<" reachability of given state is = "<< r<<" [0 --> the given state is unreachable/ 1 --> given state is reachable]"<<endl;
//    MyManager.print_table();
//}
