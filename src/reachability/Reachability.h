//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"
#include "Reachability.h"
#include <iostream>
#include <string>
#include <vector>

namespace ClassProject {


    class Reachability : public ReachabilityInterface {

    public:

        vector<BDD_ID> stateBits;
        vector<bool> stateVector;
        vector<bool> initialState;
        vector<BDD_ID> deltaBits;
        vector<BDD_ID> transitionFunctions;
        vector<BDD_ID> nextStateBits;


        explicit Reachability(unsigned int stateSize);

        const std::vector<BDD_ID> &getStates() const;

        bool isReachable(const std::vector<bool> &stateVector);

        void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions);

        void setInitState(const std::vector<bool> &stateVector);

        BDD_ID ComputeReachableStates();
        
    };

}
#endif
