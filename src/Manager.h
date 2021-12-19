// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <algorithm>

using namespace std;

typedef int BDD_ID;
struct table{
    std::string node;
    BDD_ID iID, iHigh, iLow, iTopVar;
}BDD_table[100];

BDD_ID GL_Top;
bool flag = 0;

namespace ClassProject {


    class MyManager: public ManagerInterface {
    public:



        BDD_ID createVar(const std::string &label){
            GL_Top++;
            BDD_table[GL_Top].node = label;
            BDD_table[GL_Top].iID = GL_Top;
            BDD_table[GL_Top].iHigh = 1;
            BDD_table[GL_Top].iLow = 0;
            BDD_table[GL_Top].iTopVar = BDD_table[GL_Top].iID;

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

        bool isConstant(const BDD_ID f){
            if ((BDD_table[f].iID == BDD_table[f].iHigh) && (BDD_table[f].iHigh == BDD_table[f].iLow) ){
                return true;
            }
            else{
                return false;
            }
        };

        bool isVariable(const BDD_ID x){
            if ((BDD_table[x].iID == BDD_table[x].iHigh) && (BDD_table[x].iHigh == BDD_table[x].iLow) ){
                return false;
            }
            else{
                return true;
            }
        };

        BDD_ID topVar(const BDD_ID f) {
            return BDD_table[f].iTopVar;
        };

        size_t uniqueTableSize() {
            BDD_ID x;
            x = GL_Top + 1;
            return x;
        };

        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e){

            BDD_ID H1, H2, H;
            int j;
            string temp1, temp2, temp;

            if (isConstant(i)){
                if (i){
                    H = t;
                }
                else{
                    H = e;
                }
            }
            else{
                if (isConstant(t)){
                    if (t){
                        H1 = i;
                    }
                    else{
                        H1 = 0;
                    }
                }
                else{
                    temp1 = BDD_table[i].node + "*" + BDD_table[t].node;
                    for (j=0;j<uniqueTableSize();j++){
                        if (temp1 == BDD_table[j].node){
                            H1 = BDD_table[j].iID;
                        }
                    }
                }
                if (isConstant(e)){
                    if (e){
                        H2 = i;
                    }
                    else{
                        H2 = 0;
                    }
                }
                else{
                    temp2 = "!" + BDD_table[i].node + "*" + BDD_table[t].node;
                    for (j=0;j<uniqueTableSize();j++){
                        if (temp2 == BDD_table[j].node){
                            H2 = BDD_table[j].iID;
                        }
                    }
                }
                if (H1 == 0 || H2 == 0){
                    H = H1 + H2;
                }
                else{
                    temp = temp1 + "+" + temp2;
                    for (j=0;j<uniqueTableSize();j++){
                        if (temp == BDD_table[j].node){
                            H = BDD_table[j].iID;
                        }
                    }
                }
            }
            return H;
        };


        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) {

            bool terminal = 0;
            BDD_ID T,F;

            if (isConstant(f) || isConstant(x) || BDD_table[f].iTopVar > x){
                terminal = true;
            }

            if(terminal){
                return f;
            }
            if(BDD_table[f].iTopVar == x){
                return BDD_table[f].iHigh;
            }
            else{
                T = coFactorTrue ( BDD_table[f].iHigh , x ) ;
                F = coFactorTrue ( BDD_table[f].iLow , x ) ;
                return ite(BDD_table[f].iTopVar , T, F);
            }

        };

        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) {

            bool terminal = 0;
            BDD_ID T,F;

            if (isConstant(f) || isConstant(x) || BDD_table[f].iTopVar > x){
                terminal = true;
            }

            if(terminal){
                return f;
            }
            if(BDD_table[f].iTopVar == x){
                return BDD_table[f].iLow;
            }
            else{
                T = coFactorFalse ( BDD_table[f].iHigh , x ) ;
                F = coFactorFalse ( BDD_table[f].iLow , x ) ;
                return ite(BDD_table[f].iTopVar , T, F);
            }
        };

        BDD_ID coFactorTrue(const BDD_ID f) {

            bool terminal = 0;
            BDD_ID T,F;
            BDD_ID x = BDD_table[f].iTopVar;

            if (isConstant(f) || isConstant(x) || BDD_table[f].iTopVar > x){
                terminal = true;
            }

            if(terminal){
                return f;
            }
            if(BDD_table[f].iTopVar == x){
                return BDD_table[f].iHigh;
            }
            else{
                T = coFactorTrue ( BDD_table[f].iHigh , x ) ;
                F = coFactorTrue ( BDD_table[f].iLow , x ) ;
                return ite(BDD_table[f].iTopVar , T, F);
            }
        };

        BDD_ID coFactorFalse(const BDD_ID f) {

            bool terminal = 0;
            BDD_ID T,F,temp;
            BDD_ID x = BDD_table[f].iTopVar;

            if (isConstant(f) || isConstant(x) || BDD_table[f].iTopVar > x){
                terminal = true;
            }

            if(terminal){
                return f;
            }
            if(BDD_table[f].iTopVar == x){
                return BDD_table[f].iLow;
            }
            else{
                T = coFactorFalse ( BDD_table[f].iHigh , x ) ;
                F = coFactorFalse ( BDD_table[f].iLow , x ) ;
                return ite(BDD_table[f].iTopVar , T, F);
            }
        };

        BDD_ID cal(const BDD_ID i, const BDD_ID t, const BDD_ID e) {

            BDD_ID H, L, f1, g1, h1 , f0, g0, h0, temptop;
            bool x, y, z;
            int j,k = 0,l = 0;

            x = isVariable(i);
            y = isVariable(t);
            z = isVariable(e);

            if (x == true && y == true && z == true) {
                temptop = std::min({i, t, e});
            } else if (x == true && y == true && z == false) {
                temptop = std::min({i, t});
            } else if (x == true && y == false && z == true) {
                temptop = std::min({i, e});
            } else if (x == false && y == true && z == true) {
                temptop = std::min({t, e});
            } else if (x == true && y == false && z == false) {
                temptop = i;
            } else if (x == false && y == true && z == false) {
                temptop = t;
            } else if (x == false && y == false && z == true) {
                temptop = e;
            }

            if (BDD_table[temptop].iID != BDD_table[temptop].iTopVar){
                temptop = BDD_table[temptop].iTopVar;
            }

            f1 = coFactorTrue(i, temptop);
            g1 = coFactorTrue(t, temptop);
            h1 = coFactorTrue(e, temptop);

            f0 = coFactorFalse(i, temptop);
            g0 = coFactorFalse(t, temptop);
            h0 = coFactorFalse(e, temptop);

            if(isVariable(f1)){
                k++;
            }
            if(isVariable(g1)){
                k++;
            }
            if(isVariable(h1)){
                k++;
            }

            if(isVariable(f0)){
                l++;
            }
            if(isVariable(g0)){
                l++;
            }
            if(isVariable(h0)){
                l++;
            }

            if(k<2) {
                H = ite(f1, g1, h1);
            }
            else{
                H = cal(f1, g1, h1);
            }
            if(l<2){
                L = ite(f0, g0, h0);
            }
            else{
                L = cal(f0, g0, h0);
            }

            for (j = 0; j < uniqueTableSize(); j++) {
                if (temptop == BDD_table[j].iTopVar && H == BDD_table[j].iHigh && L == BDD_table[j].iLow) {
                    return BDD_table[j].iID;
                }
            }
            GL_Top++;
            BDD_table[GL_Top].iID = GL_Top;
            BDD_table[GL_Top].iHigh = H;
            BDD_table[GL_Top].iLow = L;
            BDD_table[GL_Top].iTopVar = temptop;

            return BDD_table[GL_Top].iID;

        };

        BDD_ID neg(const BDD_ID a) {
            BDD_ID temp;
            temp = cal(a, 0, 1);
            BDD_table[temp].node = "!" + BDD_table[a].node;
            return temp;
        };

        BDD_ID and2(const BDD_ID a, const BDD_ID b) {
            BDD_ID temp;
            temp = cal(a, b, 0);
            BDD_table[temp].node = BDD_table[a].node + "*" + BDD_table[b].node;
            return temp;
        };

        BDD_ID or2(const BDD_ID a, const BDD_ID b) {
            BDD_ID temp;
            temp = cal(a, 1, b);
            BDD_table[temp].node = BDD_table[a].node + "+" + BDD_table[b].node;
            return temp;
        };

        BDD_ID xor2(const BDD_ID a, const BDD_ID b) {
            BDD_ID temp;
            temp = cal(a, !b, b);
            BDD_table[temp].node = BDD_table[a].node + "⊕" + BDD_table[b].node;
            return temp;
        };

        BDD_ID nand2(const BDD_ID a, const BDD_ID b) {
            BDD_ID temp;
            temp = cal(!a, 1, !b);
            BDD_table[temp].node = BDD_table[a].node + " nand " + BDD_table[b].node;
            return temp;
        };

        BDD_ID nor2(const BDD_ID a, const BDD_ID b) {
            BDD_ID temp;
            temp = cal(!a, !b, 0);
            BDD_table[temp].node = BDD_table[a].node + " nor " + BDD_table[b].node;
            return temp;
        };

        BDD_ID xnor2(const BDD_ID a, const BDD_ID b) {
            BDD_ID temp;
            temp = cal(a, b, !b);
            BDD_table[temp].node = BDD_table[a].node + "⊙" + BDD_table[b].node;
            return temp;
        };

        std::string getTopVarName(const BDD_ID &root) {
            BDD_ID temp;
            temp = BDD_table[root].iTopVar;
            return BDD_table[temp].node;
        };

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {

            BDD_ID x = root, y = root;
            nodes_of_root.insert(root);
            nodes_of_root.insert(BDD_table[root].iHigh);
            nodes_of_root.insert(BDD_table[root].iLow);
            while(x!=BDD_table[y].iTopVar) {
                x = BDD_table[y].iTopVar;
                nodes_of_root.insert(BDD_table[x].iHigh);
                nodes_of_root.insert(BDD_table[x].iLow);
                x = BDD_table[x].iID;
                y = x;
            }

        };

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {

            BDD_ID x = root, y = root;
            vars_of_root.insert(root);
            while(x!=BDD_table[y].iTopVar) {
                x = BDD_table[y].iTopVar;
                vars_of_root.insert(x);
                x = BDD_table[x].iID;
                y = x;
            }
        };

    };

}

#endif
