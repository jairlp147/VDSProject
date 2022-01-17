// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

typedef int BDD_ID;

struct table{
    std::string node;
    BDD_ID iID, iHigh, iLow, iTopVar;
};

namespace ClassProject {

    class Manager: public ManagerInterface {

    private:

        vector<table> unique_table;  //create vector of dataype structure //vector table "unique_table" here so it's private access

    public:

        Manager(); //constructor

        vector<table> popVector(vector<table> unique_table, BDD_ID bdd_id, BDD_ID high, BDD_ID low, BDD_ID topVar, string nodeName); //add new vector

        void reset_table();

        void print_table();

        BDD_ID TopVariable_3(const BDD_ID a,const BDD_ID b,const BDD_ID c);

        BDD_ID find_or_add_unique_table(const BDD_ID TopVariable,const BDD_ID r_high,const BDD_ID r_low);

        BDD_ID createVar(const std::string &label);

        const BDD_ID &True();

        const BDD_ID &False();

        bool isConstant(const BDD_ID f);

        bool isVariable(const BDD_ID x);

        BDD_ID topVar(const BDD_ID f);

        size_t uniqueTableSize();

        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e);

        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x = -1);

        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x=-1);

        BDD_ID neg(const BDD_ID a);

        BDD_ID and2(const BDD_ID a, const BDD_ID b);

        BDD_ID or2(const BDD_ID a, const BDD_ID b);

        BDD_ID xor2(const BDD_ID a, const BDD_ID b);

        BDD_ID nand2(const BDD_ID a, const BDD_ID b);

        BDD_ID nor2(const BDD_ID a, const BDD_ID b);

        BDD_ID xnor2(const BDD_ID a, const BDD_ID b);

        std::string getTopVarName(const BDD_ID &root);

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);
    };
}

#endif
