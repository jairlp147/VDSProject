//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

void ClassProject::Reachability::ReachabilityInterface(unsigned int stateSize) {

    string S;
    if (stateSize == 0){
        throw runtime_error(" State size cannot be zero");
    }
    else{
        for(int i = 0; i< stateSize; i++){
            S = "s" + to_string(i);
            stateBits.push_back(createVar(S));
        }
        for(int i = 0; i< stateSize; i++){
            S = "s'" + to_string(i);
            nextStateBits.push_back(createVar(S));
        }
    }

}

const std::vector<BDD_ID> & ClassProject::Reachability::getStates() const{

    return stateBits;
}

void ClassProject::Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){
    string S;

    if (transitionFunctions.size() != stateBits.size()){
        throw runtime_error("The number of given transition functions does not match the number of state bits");
    }
    else{
        for(int i = 0; i< transitionFunctions.size(); i++){
//            S = "Delta" + to_string(transitionFunctions.size()-i-1);
//            unique_table[uniqueTableSize()-i-1].node = S;
            deltaBits = transitionFunctions;
        }
    }
}

bool ClassProject::Reachability::isReachable(const std::vector<bool> &stateVector){

    BDD_ID T = 1,Cs = 1,temp[stateBits.size()],img_nextStateBits,img_stateBits,CRit,CR,tempx,tempy,f,reachable;
    bool result;

    if (stateVector.size() != stateBits.size()){
        throw runtime_error("The number of values does not match the number of state bits");
    }
    else{


        for(int i = 0; i<stateBits.size();i++) {

            //Compute Tow
            tempx = or2(and2(nextStateBits[i], deltaBits[i]), and2(neg(nextStateBits[i]), neg(deltaBits[i])));
            T = and2(tempx, T);

            //Compute Cs
            tempy = neg(xor2(stateBits[i], initialState[i]));
            Cs = and2(tempy, Cs);

        }

        CRit = Cs;

        do{
            CR = CRit;

            //Compute img(s0',s1')
            temp[0] = and2(CR,T);
            for(int i = 1; i<stateBits.size();i++) {
                temp[i] = or2(coFactorTrue(temp[i - 1], stateBits[i]), coFactorFalse(temp[i - 1], stateBits[i]));
            }
            img_nextStateBits = or2(coFactorTrue(temp[stateBits.size()-1], stateBits[0]), coFactorFalse(temp[stateBits.size()-1], stateBits[0]));

            //Compute img(s0,s1)
            temp[0] = 1;
            for(int i = 0; i<stateBits.size();i++) {
                tempy = neg(xor2(stateBits[i], nextStateBits[i]));
                temp[0] = and2(tempy, temp[0]);
            }
            temp[0] = and2(temp[0],img_nextStateBits);
            for(int i = 1; i<stateBits.size();i++) {
                temp[i] = or2(coFactorTrue(temp[i - 1], nextStateBits[i]), coFactorFalse(temp[i - 1], nextStateBits[i]));
            }
            img_stateBits = or2(coFactorTrue(temp[stateBits.size()-1], nextStateBits[0]), coFactorFalse(temp[stateBits.size()-1], nextStateBits[0]));
            //Compute New CRit
            CRit = or2(CR,img_stateBits);

        }while(CRit != CR);
        f=CR;

        // Compute reachability of given state bits
        reachable=f;
        for (int i = 0; i < stateBits.size(); ++i) {
            if(stateVector[i]== false){
                reachable=coFactorFalse(reachable,stateBits[i]);
            }
            else{
                reachable=coFactorTrue(reachable,stateBits[i]);
            }
        }
        if(reachable==0){
            result= false;
        }
        else{
            result= true;
        }
        return result;
    }

}

void ClassProject::Reachability::setInitState(const std::vector<bool> &stateVector) {

    if (stateVector.size() != stateBits.size()) {
        throw runtime_error("The number of values does not match the number of state bits");
    } else {
        for (int i = 0; i < stateVector.size(); i++) {
            initialState.push_back(stateVector[i]);
        }
    }

}

// Verification for the code with the example is included in main_test.cpp in commented form
//TODO: how to instantiate Reachability module???