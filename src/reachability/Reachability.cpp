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
            NextstateBits.push_back(createVar(S));
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

}

void ClassProject::Reachability::setInitState(const std::vector<bool> &stateVector){

    if (stateVector.size() != stateBits.size()){
        throw runtime_error("The number of values does not match the number of state bits");
    }
    else{
        for(int i = 0; i< stateVector.size(); i++){
            initialState.insert(stateVector[i]);
        }
    }

}