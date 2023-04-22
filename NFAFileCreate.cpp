#include "NFA.h"
#include "NFAFileCreate.h"
#include <string>
#include <vector>


RegularExpressionOperations::RegularExpressionOperations(){
    for(auto i : symbols){
        this->symbols.push_back(i);
    }
};

NFA* RegularExpressionOperations::UniosOperation(NFA* const leftNFA, NFA* const rightNFA){
    NFA* returnNFA = new NFA{*leftNFA};
    int leftNFAStartId;
    int leftNFAEndId;
    int rightNFAStartId;
    int rightNFAEndtId;
    for(int i{0};i<leftNFA->GetNumberOfStates();i++){
        if(leftNFA->States[i]->GetStateType() == StateType::START)
            leftNFAStartId = leftNFA->States[i]->getStateNumber();
        if(leftNFA->States[i]->GetStateType() == StateType::ACCEPTING)
            leftNFAEndId = leftNFA->States[i]->getStateNumber();       
    }
    for(int i{0};i<rightNFA->GetNumberOfStates();i++){
        if(rightNFA->States[i]->GetStateType() == StateType::START)
            rightNFAStartId = rightNFA->States[i]->getStateNumber();
        if(rightNFA->States[i]->GetStateType() == StateType::ACCEPTING)
            rightNFAEndtId = rightNFA->States[i]->getStateNumber();   
    }
    // State* startState = new State(0);

}

NFA* RegularExpressionOperations::ConcatOperation(NFA* const leftNFA, NFA* const rightNFA){

}

NFA* RegularExpressionOperations::IterationOperation(NFA* const originalNFA){

}

NFA* RegularExpressionOperations::PlusOperation(NFA* const originalNFA){

}