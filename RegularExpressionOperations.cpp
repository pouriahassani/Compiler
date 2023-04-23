#include "RegularExpressionOperations.h"
#include "NFA.h"
#include <string>
#include <vector>
#include <algorithm>

RegularExpressionOperations::RegularExpressionOperations(){
    for(auto i : symbols){
        this->symbols.push_back(i);
    }
};

NFA* RegularExpressionOperations::UnionsOperation(NFA& leftNFA, NFA& rightNFA){
    int leftNFAStartId;
    int leftNFAEndId;
    int rightNFAStartId;
    int rightNFAEndId;

    int incrementRightStateNoms = leftNFA.States.size()+2;

    for(auto currState = rightNFA.States.begin() ; currState != rightNFA.States.end() ; currState++){
        (*currState)->IncrementStateNumbers(incrementRightStateNoms);
        (*currState)->IncrementNonEpsClosureStateNumbers(incrementRightStateNoms);
        (*currState)->IncrementEpsClosureStateNumbers(incrementRightStateNoms);
    }

    for(auto currState = leftNFA.States.begin() ; currState != leftNFA.States.end() ; currState++){
        (*currState)->IncrementStateNumbers(2);
        (*currState)->IncrementNonEpsClosureStateNumbers(2);
        (*currState)->IncrementEpsClosureStateNumbers(2);
    }

    for(int i{0};i<leftNFA.States.size();i++){
        if(leftNFA.States[i]->GetStateType() == StateType::START)
            leftNFAStartId = i;
        if(leftNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            leftNFAEndId = i;
    }
    for(int i{0};i<rightNFA.States.size();i++){
        if(rightNFA.States[i]->GetStateType() == StateType::START)
            rightNFAStartId = i;
        if(rightNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            rightNFAEndId = i;
    }

    leftNFA.States[leftNFAStartId]->SetStateType(StateType::TRANSITION);
    leftNFA.States[leftNFAEndId]->SetStateType(StateType::TRANSITION);

    rightNFA.States[rightNFAStartId]->SetStateType(StateType::TRANSITION);
    rightNFA.States[rightNFAEndId]->SetStateType(StateType::TRANSITION);

    State* startState = new State(0,StateType::START); 
    State* endState = new State(1,StateType::ACCEPTING);

    startState->setEpsClosure(leftNFA.States[leftNFAStartId]->getStateNumber());
    startState->setEpsClosure(rightNFA.States[rightNFAStartId]->getStateNumber());

    leftNFA.States[leftNFAEndId]->setEpsClosure(1);
    rightNFA.States[rightNFAEndId]->setEpsClosure(1);

    NFA* returnNFA = new NFA{leftNFA};

    for(int i{0} ; i < rightNFA.States.size() ; i++){
        returnNFA->States.push_back(rightNFA.States[i]);
    }

    returnNFA->States.push_back(startState);
    returnNFA->States.push_back(endState);

    returnNFA->PrintNFA();
    // rightNFA.PrintNFA();

    return returnNFA;
}

NFA* RegularExpressionOperations::ConcatOperation(NFA& leftNFA, NFA& rightNFA){
    int leftNFAStartId;
    int leftNFAEndId;
    int rightNFAStartId;
    int rightNFAEndId;

    int incrementRightStateNoms = leftNFA.States.size() - 1;

    for(auto currState = rightNFA.States.begin() ; currState != rightNFA.States.end() ; currState++){
        (*currState)->IncrementStateNumbers(incrementRightStateNoms);
        (*currState)->IncrementNonEpsClosureStateNumbers(incrementRightStateNoms);
        (*currState)->IncrementEpsClosureStateNumbers(incrementRightStateNoms);
    }

    for(int i{0};i<leftNFA.States.size();i++){
        if(leftNFA.States[i]->GetStateType() == StateType::START)
            leftNFAStartId = i;
        if(leftNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            leftNFAEndId = i;
    }
    for(int i{0};i<rightNFA.States.size();i++){
        if(rightNFA.States[i]->GetStateType() == StateType::START)
            rightNFAStartId = i;
        if(rightNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            rightNFAEndId = i;
    }

    leftNFA.States[leftNFAEndId]->SetStateType(StateType::TRANSITION);
    for(auto i : rightNFA.States[rightNFAStartId]->GetEpsClosure()){
        leftNFA.States[leftNFAEndId]->AddEpsEdge(i);   
    }

    for(auto pairNonEpsRight : rightNFA.States[rightNFAStartId]->GetnonEpsClosure()){
        auto key = pairNonEpsRight.first;
        for(auto i : pairNonEpsRight.second)
                leftNFA.States[leftNFAEndId]->AddEdge(key,i);
    }
            

    rightNFA.States.erase(rightNFA.States.begin() + rightNFAStartId);
    // rightNFA.PrintNFA();
    NFA* returnNFA = new NFA{leftNFA};

    for(int i{0} ; i < rightNFA.States.size() ; i++){
        returnNFA->States.push_back(rightNFA.States[i]);
    }

       returnNFA->PrintNFA();
    return returnNFA;
}

NFA* RegularExpressionOperations::IterationOperation(NFA& originalNFA){
    int NFAStartId;
    int NFAEndId;

    for(auto currState = originalNFA.States.begin() ; currState != originalNFA.States.end() ; currState++){
        (*currState)->IncrementStateNumbers(2);
        (*currState)->IncrementNonEpsClosureStateNumbers(2);
        (*currState)->IncrementEpsClosureStateNumbers(2);
    }

    for(int i{0};i<originalNFA.States.size();i++){
        if(originalNFA.States[i]->GetStateType() == StateType::START)
            NFAStartId = i;
        if(originalNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            NFAEndId = i;
    }
    std::cout << "NFAStartId: "<<NFAStartId<<std::endl;
    std::cout << "NFAEndId: "<<NFAEndId<<std::endl;

    originalNFA.States[NFAStartId]->SetStateType(StateType::TRANSITION);
    originalNFA.States[NFAEndId]->SetStateType(StateType::TRANSITION);

    State* startState = new State(0,StateType::START); 
    State* endState = new State(1,StateType::ACCEPTING);

    startState->setEpsClosure(originalNFA.States[NFAStartId]->getStateNumber());
    startState->setEpsClosure(1);
    originalNFA.States[NFAEndId]->setEpsClosure(1);
    originalNFA.States[NFAEndId]->setEpsClosure(originalNFA.States[NFAStartId]->getStateNumber());


    originalNFA.States.push_back(startState);
    originalNFA.States.push_back(endState);

    originalNFA.PrintNFA();
    // rightNFA.PrintNFA();

    return &originalNFA;
}

NFA* RegularExpressionOperations::PlusOperation(NFA& originalNFA){
    NFA* returnNFA  = new NFA{*ConcatOperation(originalNFA,*IterationOperation(originalNFA))};
    return returnNFA;
}