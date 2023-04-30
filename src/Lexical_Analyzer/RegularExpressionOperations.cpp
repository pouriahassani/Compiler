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

NFA* RegularExpressionOperations::UnionsOperation(NFA leftNFA,NFA rightNFA){
    int leftNFAStartId;
    int leftNFAEndId;
    int rightNFAStartId;
    int rightNFAEndId;
                                                                                                                                      
 // The example of Union Oepration on two given NFAs                                                                                                                                     
 //                                                                                                           returnNFA                  
 //                                                                                                              ||                      
 //                                                                                                              \/                       
 //                                                                                                          4 ----- 5                   
 //                                                                                                        /           \                 
 //                           left NFA                       right NFA                               2 -->               3               
 //                              ||                              ||                               /        \           /     \           
 //                              \/                              \/                             /            6 ----- 7         \         
 //                          2 ----- 3                       2 ----- 3                        /                                  \       
 //                        /           \                   /           \                    /                                      \     
 //                  0 -->               1           0 -->               1     ====>> 0 -->                                         1   
 //                        \           /                   \           /                    \                                      /     
 //                          4 ----- 5                       4 ----- 5                        \                                  /       
 //                                                                                             \           10 ----- 11        /         
 //                                                                                              \         /           \     /           
 //                                                                                                  8 -->               9               
 //                                                                                                        \           /                 
 //                                                                                                         12 ----- 13                 
    int incrementRightStateNoms = leftNFA.States.size()+2;
    NFA* returnNFA = new NFA;
    for(auto currState = rightNFA.States.cbegin() ; currState != rightNFA.States.cend() ; currState++){
        State* newState = new State(*currState->second);
        newState->IncrementStateNumbers(incrementRightStateNoms);
        newState->IncrementNonEpsClosureStateNumbers(incrementRightStateNoms);
        newState->IncrementEpsClosureStateNumbers(incrementRightStateNoms);
        returnNFA->States[newState->GetStateNumber()] = newState;
        if(newState->GetStateType() == StateType::START)
            rightNFAStartId = newState->GetStateNumber();
        if(newState->GetStateType() == StateType::ACCEPTING)
            rightNFAEndId = newState->GetStateNumber();
    }

    for(auto currState = leftNFA.States.cbegin() ; currState != leftNFA.States.cend() ; currState++){
        State* newState = new State(*currState->second);
        newState->IncrementStateNumbers(2);
        newState->IncrementNonEpsClosureStateNumbers(2);
        newState->IncrementEpsClosureStateNumbers(2);
        returnNFA->States[newState->GetStateNumber()] = newState;
        if(newState->GetStateType() == StateType::START)
            leftNFAStartId = newState->GetStateNumber();
        if(newState->GetStateType() == StateType::ACCEPTING)
            leftNFAEndId = newState->GetStateNumber();
    }

    returnNFA->States[leftNFAStartId]->SetStateType(StateType::TRANSITION);
    returnNFA->States[leftNFAEndId]->SetStateType(StateType::TRANSITION);

    returnNFA->States[rightNFAStartId]->SetStateType(StateType::TRANSITION);
    returnNFA->States[rightNFAEndId]->SetStateType(StateType::TRANSITION);

    State* startState = new State(0,StateType::START); 
    State* endState = new State(1,StateType::ACCEPTING);

    startState->setEpsClosure(returnNFA->States[leftNFAStartId]->GetStateNumber());
    startState->setEpsClosure(returnNFA->States[rightNFAStartId]->GetStateNumber());

    returnNFA->States[leftNFAEndId]->setEpsClosure(1);
    returnNFA->States[rightNFAEndId]->setEpsClosure(1);

    returnNFA->States[0] = startState;
    returnNFA->States[1] = endState;
    
    return returnNFA;
}

NFA* RegularExpressionOperations::ConcatOperation(NFA leftNFA,NFA rightNFA){
    int leftNFAStartId =0;
    int leftNFAEndId=1;
    int rightNFAStartId=0;
    int rightNFAEndId=1;
    int incrementRightStateNoms = leftNFA.States.size()-1   ;
// The example of Concatination Oepration on two given NFAs 
//  
//                           left NFA                       right NFA                                     ReturnNFA                
//                              ||                              ||                                           ||                    
//                                                              \/                                           \/                    
//                          2 ----- 3                       2 ----- 3                           2 ----- 3          7 ----- 8       
//                        /           \                   /           \                       /           \      /           \     
//                  0 -->               1           0 -->               1    ====>>     0 -->               6-->               1   
//                        \           /                   \           /                       \           /      \           /     
//                          4 ----- 5                       4 ----- 5                           4 ----- 5          9 ----- 10      
//                                                                                                                                 
                                                                                                                                   
    NFA* returnNFA = new NFA;

    for(auto currState = rightNFA.States.cbegin() ; currState != rightNFA.States.cend() ; currState++){
        State* newState = new State(*currState->second);
        newState->IncrementStateNumbers(incrementRightStateNoms);
        newState->IncrementNonEpsClosureStateNumbers(incrementRightStateNoms);
        newState->IncrementEpsClosureStateNumbers(incrementRightStateNoms);

        newState->UpdateEpsFromOldStateNumToNew(incrementRightStateNoms+1, -1);
        newState->UpdateNonEpsFromOldStateNumToNew(incrementRightStateNoms+1 , -1);
        newState->UpdateEpsFromOldStateNumToNew(incrementRightStateNoms , -2);
        newState->UpdateNonEpsFromOldStateNumToNew(incrementRightStateNoms , -2);

        newState->UpdateEpsFromOldStateNumToNew(-1, 1);
        newState->UpdateNonEpsFromOldStateNumToNew(-1 , 1);

        newState->UpdateEpsFromOldStateNumToNew(-2, incrementRightStateNoms+1);
        newState->UpdateNonEpsFromOldStateNumToNew(-2, incrementRightStateNoms+1);

        if(newState->GetStateType() == StateType::START){
            rightNFAStartId = newState->GetStateNumber();  
            if(incrementRightStateNoms == 1){
                newState->SetStateNumber(-1);
                returnNFA->States[-1] = newState;
                rightNFAStartId = -1;
                // newState->PrintState();
            }
        }

        if(newState->GetStateType() == StateType::ACCEPTING){
            rightNFAEndId = newState->GetStateNumber();
            newState->SetStateNumber(1);
        }
        returnNFA->States[newState->GetStateNumber()] = newState;
    }


    State* middleState = new State(*returnNFA->States[rightNFAStartId]);

    returnNFA->States.erase(rightNFAStartId);


    for(auto currState = leftNFA.States.cbegin() ; currState != leftNFA.States.cend() ; currState++){
        State* newState = new State(*currState->second);
        newState->UpdateEpsFromOldStateNumToNew(1 , incrementRightStateNoms+1);
        newState->UpdateNonEpsFromOldStateNumToNew(1 , incrementRightStateNoms+1);
        if(newState->GetStateType() == StateType::START)
            leftNFAStartId = newState->GetStateNumber();
        if(newState->GetStateType() == StateType::ACCEPTING){
            newState->SetStateNumber(incrementRightStateNoms + 1);
            leftNFAEndId = newState->GetStateNumber();
        }
        returnNFA->States[newState->GetStateNumber()] = newState;
    }
    for(auto Eps : middleState->GetEpsClosure())
        returnNFA->States[leftNFAEndId]->AddEpsEdge(Eps);

    for(auto NonEpsPair : middleState->GetnonEpsClosure()){
        for(auto NonEpsId: NonEpsPair.second)
            returnNFA->States[leftNFAEndId]->AddEdge(NonEpsPair.first,NonEpsId);
    }

    for(auto& currState : returnNFA->States){
        currState.second->SetStateType(StateType::TRANSITION);
    }
    returnNFA->States[0]->SetStateType(StateType::START);
    returnNFA->States[1]->SetStateType(StateType::ACCEPTING);
    // returnNFA->PrintNFA();
    return returnNFA;
}

NFA* RegularExpressionOperations::IterationOperation(NFA originalNFA){
    int NFAStartId;
    int NFAEndId;
    NFA* returnNFA = new NFA;
    int incrementEndID = originalNFA.States.size();
    for(auto currState = originalNFA.States.cbegin() ; currState != originalNFA.States.cend() ; currState++){
        State* newState = new State(*currState->second);
        newState->IncrementStateNumbers(2);
        newState->IncrementNonEpsClosureStateNumbers(2);
        newState->IncrementEpsClosureStateNumbers(2);


        if(newState->GetStateType() == StateType::START)
            NFAStartId = newState->GetStateNumber();  

        if(newState->GetStateType() == StateType::ACCEPTING){
            NFAEndId = newState->GetStateNumber();
        }
           
        
        returnNFA->States[newState->GetStateNumber()] = newState;
    }
    
    returnNFA->States[NFAStartId]->SetStateType(StateType::TRANSITION);
    returnNFA->States[NFAEndId]->SetStateType(StateType::TRANSITION);

    State* startState = new State(0,StateType::START); 
    State* endState = new State(1,StateType::ACCEPTING);

    startState->setEpsClosure(NFAStartId);
    startState->setEpsClosure(1);
    returnNFA->States[NFAEndId]->setEpsClosure(1);
    returnNFA->States[NFAEndId]->setEpsClosure(NFAStartId);


    returnNFA->States[1] = endState;
    returnNFA->States[0] = startState;
    return returnNFA;
}

NFA* RegularExpressionOperations::PlusOperation(NFA originalNFA){
    NFA* returnNFA = ConcatOperation(originalNFA,*IterationOperation(originalNFA));
    return returnNFA;
}

NFA* RegularExpressionOperations::oneInstance(NFA originalNFA){
    int NFAEndId;
    int NFAStartId;

    for(int i{0};i<originalNFA.States.size();i++){
        if(originalNFA.States[i]->GetStateType() == StateType::START)
            NFAStartId = i;
        if(originalNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            NFAEndId = i;
    }

    originalNFA.States[NFAStartId]->AddEpsEdge(NFAEndId);
    NFA* returnNFA = new NFA{originalNFA};

    return returnNFA;
}