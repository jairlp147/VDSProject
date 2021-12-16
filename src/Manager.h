// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"

typedef int BDD_ID;
struct table{
    std::string node;
    BDD_ID iID, iHigh, iLow, iTopVar;
}BDD_table[5];

int GL_Top;

namespace ClassProject {

    class MyManager: public ManagerInterface {
    public:
        BDD_ID createVar(const std::string &label){
            GL_Top++;
            BDD_table[GL_Top].node = label;
            BDD_table[GL_Top].iID = GL_Top;

            return BDD_table[GL_Top].iID;
        };

        const BDD_ID True1(){
            BDD_table[1].node = "True";
            BDD_table[1].iID = 1;
            BDD_table[1].iHigh = 1;
            BDD_table[1].iLow = 1;
            BDD_table[1].iTopVar = 1;

            GL_Top = BDD_table[1].iID;
            return BDD_table[1].iID;
        };

        const BDD_ID False1(){
            BDD_table[0].node = "False";
            BDD_table[0].iID = 0;
            BDD_table[0].iHigh = 0;
            BDD_table[0].iLow = 0;
            BDD_table[0].iTopVar = 0;

            GL_Top = BDD_table[0].iID;
            return BDD_table[0].iID;
        };

        bool isConstant(BDD_ID f){
            if ((BDD_table[f].iID == BDD_table[f].iHigh) && (BDD_table[f].iHigh == BDD_table[f].iLow) ){
                return true;
            }
            else{
                return false;
            }
        };

        bool isVariable(BDD_ID x){
            if ((BDD_table[x].iID == BDD_table[x].iHigh) && (BDD_table[x].iHigh == BDD_table[x].iLow) ){
                return false;
            }
            else{
                return true;
            }
        };

        BDD_ID topVar(BDD_ID f) {
            return BDD_table[f].iTopVar;
        };

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) { return 0;};

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) { return 0;};

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) { return 0;};

        BDD_ID coFactorTrue(BDD_ID f) { return 0;};

        BDD_ID coFactorFalse(BDD_ID f) { return 0;};

        BDD_ID neg(BDD_ID a) {
            BDD_ID temp;
            temp = ite(a, 0, 1);
            return temp;
        };

        BDD_ID and2(BDD_ID a, BDD_ID b) {
            BDD_ID temp;
            temp = ite(a, b, 0);
            return temp;
        };

        BDD_ID or2(BDD_ID a, BDD_ID b) {
            BDD_ID temp;
            temp = ite(a, 1, b);
            return temp;
        };

        BDD_ID xor2(BDD_ID a, BDD_ID b) {
            BDD_ID temp;
            temp = ite(a, !b, b);
            return temp;
        };

        BDD_ID nand2(BDD_ID a, BDD_ID b) {
            BDD_ID temp;
            temp = ite(!a, 1, !b);
            return temp;
        };

        BDD_ID nor2(BDD_ID a, BDD_ID b) {
            BDD_ID temp;
            temp = ite(!a, !b, 0);
            return temp;
        };

        BDD_ID xnor2(BDD_ID a, BDD_ID b) {
            BDD_ID temp;
            temp = ite(a, b, !b);
            return temp;
        };

        std::string getTopVarName(const BDD_ID &root) {
            BDD_ID temp;
            temp = BDD_table[root].iTopVar;
            return BDD_table[temp].node;
        };

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) { };

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) { };

        size_t uniqueTableSize() { return 0;};
    };

}

#endif
