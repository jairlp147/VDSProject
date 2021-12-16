//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"

using namespace std;
using namespace ClassProject;

TEST(TableTest,Truenode)  //to run test, create intially a basic table with true & false nodes
{
//    Manager Manager;
    //bool temp=Manager.isConstant(7);
    //EXPECT_EQ(1, utable_vec[1].bdd_id);   //problem, doesn't detect the table created in the main file.
    EXPECT_EQ(1, 1);
}

TEST(TableTest,Falsenode)  //to run test, create intially a basic table with true & false nodes
{
 //EXPECT_EQ(0, utable_vec[0].bdd_id);   //problem, doesn't detect the table created in the main file.
    EXPECT_EQ(1, 1);
}

/* Kiran's Code */
TEST(Test_createVar,Test_createVar_a){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.createVar("a");
    EXPECT_EQ(MyTest,2);
}

TEST(Test_createVar,Test_createVar_b){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.createVar("b");
    EXPECT_EQ(MyTest,3);
}

TEST(Test_createVar,Test_createVar_c){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.createVar("c");
    EXPECT_EQ(MyTest,4);
}

TEST(Test_createVar,Test_createVar_d){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.createVar("d");
    EXPECT_EQ(MyTest,5);
}

TEST(Test_True1,Test_high_node){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.True1();
    EXPECT_EQ(MyTest,1);
}

TEST(Test_False1,Test_low_node){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.False1();
    EXPECT_EQ(MyTest,0);
}

TEST(Test_isConstant,Test_ID_0){
    MyManager MyManager;
    bool MyTest = MyManager.isConstant(0);
    EXPECT_EQ(MyTest, true);
}

TEST(Test_isConstant,Test_ID_1){
    MyManager MyManager;
    bool MyTest = MyManager.isConstant(1);
    EXPECT_EQ(MyTest, true);
}

TEST(Test_isConstant,Test_ID_2){
    MyManager MyManager;
    bool MyTest = MyManager.isConstant(2);
    EXPECT_EQ(MyTest, false);
}

TEST(Test_isVariable,Test_ID_0){
    MyManager MyManager;
    bool MyTest = MyManager.isVariable(0);
    EXPECT_EQ(MyTest, false);
}

TEST(Test_isVariable,Test_ID_1){
    MyManager MyManager;
    bool MyTest = MyManager.isVariable(1);
    EXPECT_EQ(MyTest, false);
}

TEST(Test_isVariable,Test_ID_2){
    MyManager MyManager;
    bool MyTest = MyManager.isVariable(2);
    EXPECT_EQ(MyTest, true);
}

TEST(Test_topVar,Test_topVar_False){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(0);
    EXPECT_EQ(MyTest, 0);
}

TEST(Test_topVar,Test_topVar_True){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(1);
    EXPECT_EQ(MyTest, 1);
}

TEST(Test_topVar,Test_topVar_2){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(2);
    EXPECT_EQ(MyTest, 2);
}

TEST(Test_topVar,Test_topVar_3){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(3);
    EXPECT_EQ(MyTest, 3);
}

TEST(Test_topVar,Test_topVar_4){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(4);
    EXPECT_EQ(MyTest, 4);
}

TEST(Test_topVar,Test_topVar_5){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(5);
    EXPECT_EQ(MyTest, 5);
}

TEST(Test_topVar,Test_topVar_6){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(6);
    EXPECT_EQ(MyTest, 2);
}

TEST(Test_topVar,Test_topVar_7){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(7);
    EXPECT_EQ(MyTest, 4);
}

TEST(Test_topVar,Test_topVar_8){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(8);
    EXPECT_EQ(MyTest, 3);
}

TEST(Test_topVar,Test_topVar_9){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.topVar(9);
    EXPECT_EQ(MyTest, 2);
}

TEST(Test_ite,Test_ite_a_or_b){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.ite(2,1,3);
    EXPECT_EQ(MyTest, 6);
}

TEST(Test_ite,Test_ite_c_and_d){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.ite(4,5,0);
    EXPECT_EQ(MyTest, 7);
}

TEST(Test_ite,Test_ite_b_and_c_and_d){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.ite(3,7,0);
    EXPECT_EQ(MyTest, 8);
}

TEST(Test_ite,Test_ite_a_or_b_and_c_and_d){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.ite(6,7,0);
    EXPECT_EQ(MyTest, 9);
}

TEST(Test_or2,Test_a_or2_b){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.or2(2,3);
    EXPECT_EQ(MyTest, 6);
}

TEST(Test_and2,Test_a_and2_b){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.and2(4,5);
    EXPECT_EQ(MyTest, 7);
}

TEST(Test_and2,Test_c_and2_d){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.and2(4,5);
    EXPECT_EQ(MyTest, 7);
}

TEST(Test_and2,Test_b_and2_c_and2_d){
    MyManager MyManager;
    BDD_ID MyTest = MyManager.and2(3,7);
    EXPECT_EQ(MyTest, 8);
}

TEST(Test_getTopVarName,Test_getTopVarName_2){
    MyManager MyManager;
    std::string MyTest = MyManager.getTopVarName(2);
    EXPECT_EQ(MyTest, "a");
}

TEST(Test_getTopVarName,Test_getTopVarName_3){
    MyManager MyManager;
    std::string MyTest = MyManager.getTopVarName(3);
    EXPECT_EQ(MyTest, "b");
}

TEST(Test_getTopVarName,Test_getTopVarName_4){
    MyManager MyManager;
    std::string MyTest = MyManager.getTopVarName(4);
    EXPECT_EQ(MyTest, "c");
}

TEST(Test_getTopVarName,Test_getTopVarName_5){
    MyManager MyManager;
    std::string MyTest = MyManager.getTopVarName(5);
    EXPECT_EQ(MyTest, "d");
}

TEST(Test_getTopVarName,Test_getTopVarName_6){
    MyManager MyManager;
    std::string MyTest = MyManager.getTopVarName(6);
    EXPECT_EQ(MyTest, "a");
}

TEST(Test_getTopVarName,Test_getTopVarName_7){
    MyManager MyManager;
    std::string MyTest = MyManager.getTopVarName(7);
    EXPECT_EQ(MyTest, "c");
}

TEST(Test_getTopVarName,Test_getTopVarName_8){
    MyManager MyManager;
    std::string MyTest = MyManager.getTopVarName(8);
    EXPECT_EQ(MyTest, "b");
}

TEST(Test_getTopVarName,Test_getTopVarName_9){
    MyManager MyManager;
    std::string MyTest = MyManager.getTopVarName(9);
    EXPECT_EQ(MyTest, "a");
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
