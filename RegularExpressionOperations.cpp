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
    int incrementRightStateNoms = leftNFA.States.size()+2;
    // leftNFA.PrintNFA();
    std::cout << "\n********\nStart union********\n";
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
    // std::cout <<"ls: "<< leftNFAStartId <<" le:"<<leftNFAEndId << " RS:"<<rightNFAStartId<<" RE: "<<rightNFAEndId<<std::endl; 
    // leftNFA.PrintNFA();
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


    returnNFA->States.insert(returnNFA->States.begin(),endState);
    returnNFA->States.insert(returnNFA->States.begin(),startState);

    // std::cout << "\n\n*******\nprint union NFA\n" << std::endl;
    // returnNFA->PrintNFA();
    // rightNFA.PrintNFA();
        std::cout << "\n********\nend union********\n";
        std::cout << "\n*** Not matching in union***\n";
        for(int i{0};i<returnNFA->GetStates().size();i++){
            if(i != returnNFA->GetStates().at(i)->getStateNumber()){
                std::cout << i << ": " << returnNFA->GetStates().at(i)->getStateNumber();
                returnNFA->GetStates().at(i)->PrintStateType();
            }
                
        }
    return returnNFA;
}

NFA* RegularExpressionOperations::ConcatOperation(NFA leftNFA,NFA rightNFA){
    int leftNFAStartId =0;
    int leftNFAEndId=1;
    int rightNFAStartId=0;
    int rightNFAEndId=1;
    int incrementRightStateNoms = leftNFA.States.size()+1;
    std::cout << "\n********\n"<<incrementRightStateNoms<<"\nStart ConcatOperation********\n";
// rightNFA.PrintNFA();

    for(auto currState = rightNFA.States.begin() ; currState != rightNFA.States.end() ; currState++){
        (*currState)->IncrementStateNumbers(incrementRightStateNoms);
        (*currState)->IncrementNonEpsClosureStateNumbers(incrementRightStateNoms);
        (*currState)->IncrementEpsClosureStateNumbers(incrementRightStateNoms);
    }

    // for(auto currState = leftNFA.States.begin() ; currState != leftNFA.States.end() ; currState++){
    //     (*currState)->IncrementStateNumbers(2);
    //     (*currState)->IncrementNonEpsClosureStateNumbers(2);
    //     (*currState)->IncrementEpsClosureStateNumbers(2);
    // }

    for(int i{0};i<leftNFA.States.size();i++){
        if(leftNFA.States[i]->GetStateType() == StateType::START)
            leftNFAStartId = i;
        if(leftNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            leftNFAEndId = i;
        // std::cout << i<<" "<<leftNFA.States[i]->getStateNumber()<<" state type in the left NFA: ";
        // rightNFA.States[i]->PrintStateType();
        // std::cout <<std::endl;
    }
    for(int i{0};i<rightNFA.States.size();i++){
        if(rightNFA.States[i]->GetStateType() == StateType::START)
            rightNFAStartId = i;
        if(rightNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            rightNFAEndId = i;
        // std::cout <<i<<" "<<rightNFA.States[i]->getStateNumber()<<" state type in the right NFA: ";
        // rightNFA.States[i]->PrintStateType();
        // std::cout <<std::endl;
    }
    leftNFA.States[leftNFAEndId]->SetStateType(StateType::TRANSITION);
    // leftNFA.States[leftNFAStartId]->SetStateType(StateType::TRANSITION);
    // rightNFA.States[rightNFAEndId]->SetStateType(StateType::TRANSITION);
    // rightNFA.States[rightNFAStartId]->SetStateType(StateType::TRANSITION);
    for(auto i : rightNFA.States[rightNFAStartId]->GetEpsClosure()){
        leftNFA.States[leftNFAEndId]->AddEpsEdge(i);   
    }
    
    for(auto pairNonEpsRight : rightNFA.States[rightNFAStartId]->GetnonEpsClosure()){
        auto key = pairNonEpsRight.first;
        for(auto i : pairNonEpsRight.second)
                leftNFA.States[leftNFAEndId]->AddEdge(key,i);
    }
    
    for(auto& i : rightNFA.States){
        for(auto j: i->GetEpsClosure()){
            if(j == rightNFA.States[rightNFAStartId]->getStateNumber()){
                i->RemoveEpsClosure(j);
                i->AddEpsEdge(leftNFA.States.size());
            }
            if(j == rightNFA.States[rightNFAEndId]->getStateNumber()){
                i->RemoveEpsClosure(j);
                i->AddEpsEdge(1);
            }
                
        }
        for(auto j: i->GetnonEpsClosure()){
            if(j.second.find(rightNFA.States[rightNFAStartId]->getStateNumber()) != j.second.end()){
                i->RemoveNonEpsClosure(j.first,rightNFA.States[rightNFAStartId]->getStateNumber());
                i->AddEdge(j.first,leftNFA.States.size());
            }

            if(j.second.find(rightNFA.States[rightNFAEndId]->getStateNumber()) != j.second.end()){
                i->RemoveNonEpsClosure(j.first,rightNFA.States[rightNFAEndId]->getStateNumber());
                i->AddEdge(j.first,1);
            }
        }

    }

    for(auto& i : leftNFA.States){
        for(auto j: i->GetEpsClosure()){
            if(j == 1){
                i->RemoveEpsClosure(j);
                i->AddEpsEdge(leftNFA.States.size());
            }              
        }

        for(auto j: i->GetnonEpsClosure()){
            if(j.second.find(1) != j.second.end()){
                i->RemoveNonEpsClosure(j.first,1);
                i->AddEdge(j.first,leftNFA.States.size());
            }
        }

    }

    rightNFA.States[rightNFAEndId]->SetStateNumber(1);
    State* startState = new State(*rightNFA.States[rightNFAEndId]); 
    rightNFA.States.erase(rightNFA.States.begin());
    // rightNFA.PrintNFA();

    
    // State* endState = new State(1,StateType::ACCEPTING);

    // startState->setEpsClosure(leftNFA.States[leftNFAStartId]->getStateNumber());
    // rightNFA.States[rightNFAEndId]->setEpsClosure(1);


    NFA* returnNFA = new NFA{leftNFA};
    returnNFA->States.insert(returnNFA->States.begin()+1,startState);
    rightNFA.States.erase(rightNFA.States.begin() + rightNFAEndId);
    for(int i{0} ; i < rightNFA.States.size() ; i++){
        State *newState = new State{*rightNFA.States[i]};
        returnNFA->States.push_back(newState);
    }

    // returnNFA->States.insert(returnNFA->States.begin(),endState);
    // returnNFA->States.insert(returnNFA->States.begin(),startState);
    // std::cout << "\n\n*******\nprint concated NFA\n" << std::endl;
    // returnNFA->PrintNFA();
        std::cout << "\n********\nend ConcatOperation********\n";
        std::cout << "\n*** Not matching in ConcatOperation***\n";
        for(int i{0};i<returnNFA->GetStates().size();i++){
            if(i != returnNFA->GetStates().at(i)->getStateNumber()){
                std::cout << i << ": " << returnNFA->GetStates().at(i)->getStateNumber();
                returnNFA->GetStates().at(i)->PrintStateType();
            }
        }
    return returnNFA;
}

NFA* RegularExpressionOperations::IterationOperation(NFA originalNFA){
    int NFAStartId;
    int NFAEndId;
    std::cout << "\n********\nStart IterationOperation********\n";
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
    // std::cout << "NFAStartId: "<<NFAStartId<<std::endl;
    // std::cout << "NFAEndId: "<<NFAEndId<<std::endl;

    originalNFA.States[NFAStartId]->SetStateType(StateType::TRANSITION);
    originalNFA.States[NFAEndId]->SetStateType(StateType::TRANSITION);

    State* startState = new State(0,StateType::START); 
    State* endState = new State(1,StateType::ACCEPTING);

    startState->setEpsClosure(originalNFA.States[NFAStartId]->getStateNumber());
    startState->setEpsClosure(1);
    originalNFA.States[NFAEndId]->setEpsClosure(1);
    originalNFA.States[NFAEndId]->setEpsClosure(originalNFA.States[NFAStartId]->getStateNumber());


    originalNFA.States.insert(originalNFA.States.begin(),endState);
    originalNFA.States.insert(originalNFA.States.begin(),startState);

    // originalNFA.PrintNFA();
    // rightNFA.PrintNFA();
    std::cout << "\n********\nLast line of IterationOperation********\n";
    NFA* returnNFA = new NFA{originalNFA};
    std::cout << "\n********\nend IterationOperation********\n";
    std::cout << "\n*** Not matching in IterationOperation***\n";
    for(int i{0};i<returnNFA->GetStates().size();i++){
        if(i != returnNFA->GetStates().at(i)->getStateNumber()){
            std::cout << i << ": " << returnNFA->GetStates().at(i)->getStateNumber();
            returnNFA->GetStates().at(i)->PrintStateType();
        }
    }
    return returnNFA;
}

NFA* RegularExpressionOperations::PlusOperation(NFA originalNFA){
        std::cout << "\n********\nStart PlusOperation********\n";

    NFA* returnNFA = ConcatOperation(originalNFA,*IterationOperation(originalNFA));
            std::cout << "\n********\nend PlusOperation********\n";
    
    std::cout << "\n*** Not matching in PlusOperation***\n";
    for(int i{0};i<returnNFA->GetStates().size();i++){
        if(i != returnNFA->GetStates().at(i)->getStateNumber()){
            std::cout << i << ": " << returnNFA->GetStates().at(i)->getStateNumber();
            returnNFA->GetStates().at(i)->PrintStateType();
        }
    }

    return returnNFA;
}

NFA* RegularExpressionOperations::oneInstance(NFA originalNFA){
    int NFAEndId;
    int NFAStartId;
                std::cout << "\n********\estart oneInstance********\n";

    for(int i{0};i<originalNFA.States.size();i++){
        if(originalNFA.States[i]->GetStateType() == StateType::START)
            NFAStartId = i;
        if(originalNFA.States[i]->GetStateType() == StateType::ACCEPTING)
            NFAEndId = i;
    }

    originalNFA.States[NFAStartId]->AddEpsEdge(NFAEndId);
    // originalNFA.PrintNFA();
    NFA* returnNFA = new NFA{originalNFA};
                    std::cout << "\n********\nend oneInstance********\n";

    std::cout << "\n*** Not matching in oneInstance***\n";
    for(int i{0};i<returnNFA->GetStates().size();i++){
        if(i != returnNFA->GetStates().at(i)->getStateNumber()){
            std::cout << i << ": " << returnNFA->GetStates().at(i)->getStateNumber();
            returnNFA->GetStates().at(i)->PrintStateType();
        }
    }                    

    return returnNFA;
}