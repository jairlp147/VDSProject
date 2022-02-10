//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

using namespace ClassProject;

int main(int argc, char* argv[])
{
    //Global variables
    Manager MyManager;vector<BDD_ID> stateBits;vector<BDD_ID> nextStateBits;BDD_ID t;BDD_ID f;
///ReachabilityInterface///////
//Input
    int stateSize=2;
//Function
    string S;
    if (stateSize == 0){
        throw runtime_error(" State size cannot be zero");
    }
    else{
        for(int i = 0; i< stateSize; i++){
            S = "s" + to_string(i);
            stateBits.push_back(MyManager.createVar(S));
        }
        for(int i = 0; i< stateSize; i++){
            S = "s'" + to_string(i);
            nextStateBits.push_back(MyManager.createVar(S));
        }
    }
/////getStates///////////
    //return stateBits;
    //cout << stateBits.size();
    //cout << stateBits[1];
///////setTransitionFunctions///////////
    //Input
    vector<BDD_ID> transitionFunctions={MyManager.neg(stateBits[0]),MyManager.neg(stateBits[1])};
    //Function
    if (transitionFunctions.size() != stateBits.size()){
        throw runtime_error("The number of given transition functions does not match the number of state bits");
    }
    else{
        t=MyManager.xnor2(nextStateBits[0],transitionFunctions[0]);
        if(stateBits.size()!=1){
            for(int i = 1; i<transitionFunctions.size(); i++){
                t=MyManager.and2(t,MyManager.xnor2(nextStateBits[i],transitionFunctions[i]));
            }
        }
    }
/////////setInitState///////////
    //Input
    vector<bool> initialState={false,false};
    //Function
    BDD_ID Cs,CRit,CR;
    BDD_ID temp1;
    if (stateBits.size() != stateBits.size()) {
        throw runtime_error("The number of values does not match the number of state bits");
    } else {
        if (initialState[0]==false){
            Cs=MyManager.neg(stateBits[0]);
        }
        else{
            Cs=stateBits[0];
        }
        for(int i=1;i<stateBits.size();i++){
            if (initialState[i]==false){
                Cs=MyManager.and2(Cs,MyManager.neg(stateBits[i]));
            }
            else{
                Cs=MyManager.and2(Cs,stateBits[i]);
            }
        }
        CRit = Cs;
        do{
            CR = CRit;
            //Compute img(s0',s1')
            temp1 = MyManager.and2(CR,t);
            //Part 7
            for(int i = 0; i<stateBits.size();i++) {
                temp1 = MyManager.or2(MyManager.coFactorTrue(temp1,stateBits[i]),MyManager.coFactorFalse(temp1,stateBits[i]));
            }
            //Part 8
            for(int i = 0; i<stateBits.size();i++) {
                temp1 = MyManager.and2(temp1,MyManager.xnor2(stateBits[i],nextStateBits[i]));
            }
            for(int i = 0; i<stateBits.size();i++) {
                temp1 = MyManager.or2(MyManager.coFactorTrue(temp1,nextStateBits[i]),MyManager.coFactorFalse(temp1,nextStateBits[i]));
            }
            //Compute New CRit //Part 9
            CRit = MyManager.or2(CR,temp1);
        }while(CRit != CR);//Part 11
        f=CR;
    }
//////bool isReachable(const std::vector<bool> &stateVector);/////////
    //Input
    std::vector<bool> stateVector={true,true};
    //function
    BDD_ID reachable=f;
    bool result;
    for (int i = 0; i < stateBits.size(); ++i) {
        if(stateVector[i]== false){
            reachable=MyManager.coFactorFalse(reachable,stateBits[i]);
        }
        else{
            reachable=MyManager.coFactorTrue(reachable,stateBits[i]);
        }
    }
    if(reachable==0){
        result= false;
    }
    else{
        result= true;
    }
    //return result;

    /////////Testing///////////
    if(result){
        cout << "It's reachable" << endl;
    }
    else{
        cout << "It's unreachable" << endl;
    }

    //Print table
    MyManager.print_table();


    /*
    Manager MyManager;
    // MyManager.reset_table();  not needed anymore as constructor will call reset_table
    BDD_ID a = MyManager.createVar("a");
    BDD_ID b = MyManager.createVar("b");
    BDD_ID c = MyManager.createVar("c");
    BDD_ID d = MyManager.createVar("d");
    BDD_ID f = MyManager.and2(MyManager.and2(c,d),MyManager.or2(a,b));
    MyManager.print_table();
 //   MyManager.print_ctable();
     */
}