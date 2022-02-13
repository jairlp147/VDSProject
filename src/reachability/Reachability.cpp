//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

ClassProject::Reachability::Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize) {

    string S;
    if (stateSize == 0){
        throw runtime_error(" State size cannot be zero");
    }
    else{
        reset_table();

        for(int i = 0; i< stateSize; i++){
            S = "s" + to_string(i);
            stateBits.push_back(createVar(S));
        }
        for(int i = 0; i< stateSize; i++){
            S = "s'" + to_string(i);
            nextStateBits.push_back(createVar(S));
        }
        // Set default transition functions
        deltaBits = stateBits;
        // Set default initial state
        //initialState = {0,0};

        for(int i = 0; i< stateSize; i++){
            initialState.push_back(0);
        }

    }

}

const std::vector<BDD_ID> & ClassProject::Reachability::getStates() const{

    return stateBits;
}

void ClassProject::Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions){

    if (transitionFunctions.size() != stateBits.size()){
        throw runtime_error("The number of given transition functions does not match the number of state bits");
    }
    else{
            deltaBits = transitionFunctions;
    }
}

void ClassProject::Reachability::setInitState(const std::vector<bool> &stateVector) {

    if (stateVector.size() != stateBits.size()) {
        throw runtime_error("The number of values does not match the number of state bits");
    } else {
        initialState={};
        for (int i = 0; i < stateVector.size(); i++) {
            initialState.push_back(stateVector[i]);
        }
    }

}

BDD_ID ClassProject::Reachability::ComputeReachableStates(){
    BDD_ID T = 1,Cs = 1,temp[stateBits.size()],img_nextStateBits,img_stateBits,CRit,CR,tempx,tempy,reachable;
    bool result;


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
        return CR;

}

bool ClassProject::Reachability::isReachable(const std::vector<bool> &stateVector){

    BDD_ID reachable;

    // Compute reachability of given state bits
    reachable = ComputeReachableStates();
    if (stateVector.size() != stateBits.size()){
        throw runtime_error("The given value does not match the number of state bits");
    }
    else {
        for (int i = 0; i < stateBits.size(); ++i) {
            if (stateVector[i] == false) {
                reachable = coFactorFalse(reachable, stateBits[i]);
            } else {
                reachable = coFactorTrue(reachable, stateBits[i]);
            }
        }
        if (reachable == 0) {
            cout << "Given state is UNREACHABLE" << endl;
            return false;
        } else {
            cout << "Given state is REACHABLE" << endl;
            return true;
        }
    }
}
