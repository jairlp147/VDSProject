//
// Created by ludwig on 22.11.16.
//

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "Tests.h"



using namespace std;
using namespace ClassProject;



//int main(int argc, char* argv[])
//{
//    ::testing::InitGoogleTest(&argc, argv);
//    ClassProject::Reachability testReachability(2);
//    vector<BDD_ID> s = testReachability.getStates();
//    vector<BDD_ID> x={testReachability.neg(s[0]),testReachability.neg(s[1]),};
//
//    testReachability.setTransitionFunctions(x);
//
//    vector<bool> y= {0,0};
//    testReachability.setInitState(y);
//
//    vector<bool> z= {0,0};
//    bool r = testReachability.isReachable(z);
////    cout<<" reachability of given state is = "<< r<<" [0 --> the given state is unreachable/ 1 --> given state is reachable]"<<endl;
//    testReachability.print_table();
//
//    return RUN_ALL_TESTS();
//}

TEST(Test_defaultCondition,functions){
    ClassProject::Reachability testReachability(2);

    EXPECT_EQ(testReachability.stateBits,testReachability.deltaBits);
    vector<bool> expectedResult= {0,0};
    EXPECT_EQ(expectedResult,testReachability.initialState);

    bool result= testReachability.isReachable({0,0});
    EXPECT_EQ(true,result);
}

TEST(Test_StateReachability_00,functions){
    ClassProject::Reachability testReachability(2);

    vector<BDD_ID> s = testReachability.getStates();
    vector<BDD_ID> x={testReachability.neg(s[0]),testReachability.neg(s[1]),};
    testReachability.setTransitionFunctions(x);

    vector<bool> y= {0,0};
    testReachability.setInitState(y);

    vector<bool> z= {0,0};
    bool result = testReachability.isReachable(z);

    EXPECT_EQ(true,result);
}

TEST(Test_StateReachability_11,functions){
    ClassProject::Reachability testReachability(2);

    vector<BDD_ID> s = testReachability.getStates();
    vector<BDD_ID> x={testReachability.neg(s[0]),testReachability.neg(s[1]),};
    testReachability.setTransitionFunctions(x);

    vector<bool> y= {0,0};
    testReachability.setInitState(y);

    vector<bool> z= {1,1};
    bool result = testReachability.isReachable(z);

    EXPECT_EQ(true,result);
}

TEST(Test_StateReachability_10,functions){
    ClassProject::Reachability testReachability(2);

    vector<BDD_ID> s = testReachability.getStates();
    vector<BDD_ID> x={testReachability.neg(s[0]),testReachability.neg(s[1]),};
    testReachability.setTransitionFunctions(x);

    vector<bool> y= {0,0};
    testReachability.setInitState(y);

    vector<bool> z= {1,0};
    bool result = testReachability.isReachable(z);

    EXPECT_EQ(false,result);
}

TEST(Test_StateReachability_01,functions){
    ClassProject::Reachability testReachability(2);

    vector<BDD_ID> s = testReachability.getStates();
    vector<BDD_ID> x={testReachability.neg(s[0]),testReachability.neg(s[1]),};
    testReachability.setTransitionFunctions(x);

    vector<bool> y= {0,0};
    testReachability.setInitState(y);

    vector<bool> z= {0,1};
    bool result = testReachability.isReachable(z);

    EXPECT_EQ(false,result);
}

TEST(Test_ReachabilityInterface_runtime_error,functions){

    EXPECT_THROW( ClassProject::Reachability testReachability(0),runtime_error);
}

TEST(Test_setTransitionFunctions_runtime_error,functions){
    ClassProject::Reachability testReachability(2);
    vector<BDD_ID> x= {0,0,0,0};

    EXPECT_THROW(testReachability.setTransitionFunctions(x),runtime_error);
}

TEST(Test_setInitState_runtime_error,functions){
    ClassProject::Reachability testReachability(2);
    vector<bool> x= {0,0,0,0};

    EXPECT_THROW(testReachability.setInitState(x),runtime_error);
}

TEST(Test_isReachable_runtime_error,functions){
    ClassProject::Reachability testReachability(2);
    vector<bool> x= {0,0,0,0};

    EXPECT_THROW(testReachability.isReachable(x),runtime_error);
}

TEST(NewExample,functions){
    ClassProject::Reachability testReachability(3);
    vector<BDD_ID> s = testReachability.getStates();
    vector<BDD_ID> x={testReachability.neg(s[0]),testReachability.xor2(s[0],s[1]),testReachability.neg(s[2])};
    testReachability.setTransitionFunctions(x);
    vector<bool> y= {1,1,0};
    testReachability.setInitState(y);
    EXPECT_EQ(testReachability.isReachable({0,0,0}),false);
    EXPECT_EQ(testReachability.isReachable({1,0,0}),true);
    EXPECT_EQ(testReachability.isReachable({0,1,0}),false);
    EXPECT_EQ(testReachability.isReachable({1,1,0}),true);
    EXPECT_EQ(testReachability.isReachable({0,0,1}),true);
    EXPECT_EQ(testReachability.isReachable({1,0,1}),false);
    EXPECT_EQ(testReachability.isReachable({0,1,1}),true);
    EXPECT_EQ(testReachability.isReachable({1,1,1}),false);
}

TEST(Test_setTransitionFunctions_undefined_ID,functions){
    ClassProject::Reachability testReachability(2);
    vector<::BDD_ID> x= {1000,2000};
    EXPECT_THROW(testReachability.setTransitionFunctions(x),runtime_error);
}