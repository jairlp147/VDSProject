//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"

#include <string>
#include <set>


using namespace std;
using namespace ClassProject;

//Default value of the table
TEST(defaultvalues,unique_table){
    Manager MyManager;
    MyManager.reset_table();
    //False node test
    EXPECT_EQ(MyManager.table_element(0,"iID"),0);
    EXPECT_EQ(MyManager.table_element(0,"iHigh"),0);
    EXPECT_EQ(MyManager.table_element(0,"iLow"),0);
    EXPECT_EQ(MyManager.table_element(0,"iTopVar"),0);
    //True node test
    EXPECT_EQ(MyManager.table_element(1,"iID"),1);
    EXPECT_EQ(MyManager.table_element(1,"iHigh"),1);
    EXPECT_EQ(MyManager.table_element(1,"iLow"),1);
    EXPECT_EQ(MyManager.table_element(1,"iTopVar"),1);
    //Initial size test
    EXPECT_EQ(MyManager.uniqueTableSize(),2);
}
//No repeat a node

TEST(Test_False,Test_low_node){
    Manager MyManager;
    MyManager.reset_table();
    EXPECT_EQ(MyManager.False(),0); //Test of the False function
}

TEST(Test_True,Test_high_node){
    Manager MyManager;
    MyManager.reset_table();
    EXPECT_EQ(MyManager.True(),1); //Test of the True function
}

TEST(Test_createVar,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID MyTest = MyManager.createVar("a");
    //Value's test
    EXPECT_EQ(MyTest,2);
    EXPECT_EQ(MyManager.table_element(MyTest,"iHigh"),1);
    EXPECT_EQ(MyManager.table_element(MyTest,"iLow"),0);
    EXPECT_EQ(MyManager.table_element(MyTest,"iTopVar"),MyTest);
    //The size has to increase by 1
    EXPECT_EQ(MyManager.uniqueTableSize(),3);
}

TEST(Test_isConstant,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    EXPECT_EQ(MyManager.isConstant(MyManager.False()), true);//False is a constant
    EXPECT_EQ(MyManager.isConstant(MyManager.True()), true);//True is a constant
    EXPECT_EQ(MyManager.isConstant(a), false);//a is not a constant
}

TEST(Test_isVariable,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    EXPECT_EQ(MyManager.isVariable(MyManager.True()), false);//True is not a variable
    EXPECT_EQ(MyManager.isVariable(a), true);//a is a variable
}

TEST(Test_TopVariable,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    EXPECT_EQ(MyManager.topVar(0), 0);
    EXPECT_EQ(MyManager.topVar(1), 1);
    EXPECT_EQ(MyManager.topVar(a), a);
}

TEST(Test_ite,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    //Terminal case
    EXPECT_EQ(MyManager.ite(0,a,b), b);
    EXPECT_EQ(MyManager.ite(1,a,b), a);
    EXPECT_EQ(MyManager.uniqueTableSize(), 4);//Terminal cases don't create new nodes
    //apply the ite algorithm
    BDD_ID ite=MyManager.ite(a,1,b);//A or B
    EXPECT_EQ(ite, 4);// A new ID was created
    EXPECT_EQ(MyManager.table_element(ite,"iHigh"), 1);//Verifying with the OR behavior
    EXPECT_EQ(MyManager.table_element(ite,"iLow"), 3);//Verifying with the OR behavior
    EXPECT_EQ(MyManager.uniqueTableSize(), 5);//A new node should be created
}

//Functions require for ite
TEST(Test_TopVariable_3,ITEfunctions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID c = MyManager.createVar("c");
    EXPECT_EQ(MyManager.TopVariable_3(a,b,c), a);
    EXPECT_EQ(MyManager.TopVariable_3(b,c,a), a);
}

TEST(Test_find_or_add_unique_table,ITEfunctions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    //Find a node
    EXPECT_EQ(MyManager.find_or_add_unique_table(1,1,1), 1);//Should find the True node
    EXPECT_EQ(MyManager.find_or_add_unique_table(a,1,0), a);//Should find the A node
    //Add a node
    BDD_ID NewNode = MyManager.find_or_add_unique_table(a,0,1);//Should create a new node for not(A)
    EXPECT_EQ(NewNode, 3);//A new ID should be created
    EXPECT_EQ(MyManager.table_element(NewNode,"iHigh"), 0);
    EXPECT_EQ(MyManager.table_element(NewNode,"iLow"), 1);
}
//End of ITE functions

TEST(Test_coFactorTrue,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    //Terminal case
    EXPECT_EQ(MyManager.coFactorTrue(MyManager.True(),a), MyManager.True());
    EXPECT_EQ(MyManager.coFactorTrue(a,MyManager.True()), a);
    EXPECT_EQ(MyManager.coFactorTrue(a,b), a);
    //apply the coFactorTrue algorithm
    BDD_ID AorB = MyManager.find_or_add_unique_table(a,1,b);//Create a "A or B" node
    BDD_ID AandB = MyManager.find_or_add_unique_table(a,b,0);//Create a "A and B" node
    EXPECT_EQ(MyManager.coFactorTrue(AorB,a), 1);
    EXPECT_EQ(MyManager.coFactorTrue(AandB,a), b);
}

TEST(Test_coFactorFalse,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    //Terminal case
    EXPECT_EQ(MyManager.coFactorFalse(MyManager.True(),a), MyManager.True());
    EXPECT_EQ(MyManager.coFactorFalse(a,MyManager.True()), a);
    EXPECT_EQ(MyManager.coFactorFalse(a,b), a);
    //apply the coFactorTrue algorithm
    BDD_ID AorB = MyManager.find_or_add_unique_table(a,1,b);//Create a "A or B" node
    BDD_ID AandB = MyManager.find_or_add_unique_table(a,b,0);//Create a "A and B" node
    EXPECT_EQ(MyManager.coFactorFalse(AorB,a), b);
    EXPECT_EQ(MyManager.coFactorFalse(AandB,a), 0);
}

TEST(Test_neg,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID b = MyManager.createVar("b");
    BDD_ID negB = MyManager.neg(b);
    EXPECT_EQ(MyManager.table_element(negB,"iTopVar"), b);
    EXPECT_EQ(MyManager.table_element(negB,"iHigh"), 0);
    EXPECT_EQ(MyManager.table_element(negB,"iLow"), 1);
}

TEST(Test_and2,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID AandB = MyManager.and2(a,b);
    EXPECT_EQ(MyManager.table_element(AandB,"iTopVar"), a);
    EXPECT_EQ(MyManager.table_element(AandB,"iHigh"), b);
    EXPECT_EQ(MyManager.table_element(AandB,"iLow"), 0);
}

TEST(Test_or2,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID AorB = MyManager.or2(a,b);
    EXPECT_EQ(MyManager.table_element(AorB,"iTopVar"), a);
    EXPECT_EQ(MyManager.table_element(AorB,"iHigh"), 1);
    EXPECT_EQ(MyManager.table_element(AorB,"iLow"), b);
}

TEST(Test_xor2,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID AxorB = MyManager.xor2(a,b);
    EXPECT_EQ(MyManager.table_element(AxorB,"iTopVar"), a);
    EXPECT_EQ(MyManager.table_element(AxorB,"iHigh"), MyManager.neg(b));
    EXPECT_EQ(MyManager.table_element(AxorB,"iLow"), b);
}

TEST(Test_nand2,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID AnandB = MyManager.nand2(a,b);
    EXPECT_EQ(MyManager.table_element(AnandB,"iTopVar"), a);
    EXPECT_EQ(MyManager.table_element(AnandB,"iHigh"), MyManager.neg(b));
    EXPECT_EQ(MyManager.table_element(AnandB,"iLow"), 1);
}

TEST(Test_nor2,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID AnorB = MyManager.nor2(a,b);
    EXPECT_EQ(MyManager.table_element(AnorB,"iTopVar"), a);
    EXPECT_EQ(MyManager.table_element(AnorB,"iHigh"), 0);
    EXPECT_EQ(MyManager.table_element(AnorB,"iLow"), MyManager.neg(b));
}

TEST(Test_xnor2,functions){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID AxnorB = MyManager.xnor2(a,b);
    EXPECT_EQ(MyManager.table_element(AxnorB,"iTopVar"), a);
    EXPECT_EQ(MyManager.table_element(AxnorB,"iHigh"), b);
    EXPECT_EQ(MyManager.table_element(AxnorB,"iLow"), MyManager.neg(b));
}

TEST(Test_getTopVarName,Test_getTopVarName_2){
    Manager MyManager;
    MyManager.reset_table();
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID AxnorB = MyManager.xnor2(a,b);
    EXPECT_EQ(MyManager.getTopVarName(AxnorB), "a");
}

TEST(Test_findNodes,functions){
    Manager MyManager;
    MyManager.reset_table();
    std::set<BDD_ID> MyTest = {};
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID c = MyManager.createVar("c");
    BDD_ID d = MyManager.createVar("d");
    BDD_ID f = MyManager.and2(MyManager.and2(c,d),MyManager.or2(a,b));
    MyManager.findNodes(8,MyTest);
    std::set<BDD_ID> Result = {0,1,5,7,8};
    EXPECT_EQ(MyTest,Result);
    MyTest = {};
    MyManager.findNodes(6,MyTest);
    Result = {0,1,3,6};
    EXPECT_EQ(MyTest,Result);
}

TEST(Test_findVars,functions){
    Manager MyManager;
    MyManager.reset_table();
    std::set<BDD_ID> MyTest = {};
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID c = MyManager.createVar("c");
    BDD_ID d = MyManager.createVar("d");
    BDD_ID f = MyManager.and2(MyManager.and2(c,d),MyManager.or2(a,b));
    MyManager.findVars(8,MyTest);
    std::set<BDD_ID> Result = {3,4,5};
    EXPECT_EQ(MyTest,Result);
    MyTest = {};
    MyManager.findVars(MyManager.or2(a,b),MyTest);
    Result = {a,b};
    EXPECT_EQ(MyTest,Result);
    MyTest = {};
    MyManager.findVars(f,MyTest);
    Result = {a,b,c,d};
    EXPECT_EQ(MyTest,Result);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
