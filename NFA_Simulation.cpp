
#include "NFA_Simulation.h"
#include "NFA.h"
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

NFASimulation::NFASimulation(NFA *NFAObject) : NFAObject(NFAObject) {
  alreadyOn.resize(NFAObject->GetNumberOfStates(), false);
}

NFA* NFASimulation::GetNFAOBject(){return NFAObject;}

std::set<int> &NFASimulation::Move(std::set<int> &S, char c) {
  std::string C;
  C = std::string(1, c);
  std::set<int> returnStatesSet;
  for (auto i{S.begin()}; i != S.end(); i++) {
    int statId = *i;
    State *nxtState{NFAObject->GetStates()[statId]};
    for (int j{0}; j < nxtState->GetnonEpsClosure().size(); j++) {
      if (nxtState->GetnonEpsClosure().find(C) !=
          nxtState->GetnonEpsClosure().end()) {
        auto pairItr{*(nxtState->GetnonEpsClosure().find(C))};
        std::set<int> setItr{pairItr.second};
        for (auto k{setItr.begin()}; k != setItr.end(); k++)
          returnStatesSet.insert(*k);
      }
    }
  }
  S = returnStatesSet;
  return S;
}



std::set<int> &NFASimulation::Eclosure(std::set<int> &S) {
  std::set<int> returnStatesSet;
  for (auto i{S.begin()}; i != S.end(); i++){
    alreadyOn[*i] = true;
    oldStack.push(*i);
  }
  while (!oldStack.empty()) {
    std::set<int> setItr{
        NFAObject->GetStates()[oldStack.top()]->GetEpsClosure()};
    for (auto j{setItr.begin()}; j != setItr.end(); j++) {
      if (!alreadyOn[*j])
        addState(*j);
      oldStack.pop();
    }
  }

  while (!newStack.empty()) {
    oldStack.push(newStack.top());
    alreadyOn[newStack.top()] = false;
    returnStatesSet.insert(newStack.top());
    newStack.pop();
  }
  S = returnStatesSet;
  return S;
}

void NFASimulation::addState(int stateNumber) {
  newStack.push(stateNumber);
  alreadyOn[stateNumber] = true;
  for (auto i{NFAObject->GetStates()[stateNumber]->GetEpsClosure().begin()};
       i != NFAObject->GetStates()[stateNumber]->GetEpsClosure().end(); i++) {
    if (!alreadyOn[*i])
      addState(*i);
  }
}

void NFASimulation::Simulation(std::string line,int& lexemeSize) {
  std::set<int> S;
 
  auto c = line.begin();
  lexemeSize = 0;

  for(auto i:NFAObject->GetStates()){
    if(i->GetStateType() == StateType::START)
      oldStack.push(i->getStateNumber());
  }
  S = NFAObject->GetStates().at(oldStack.top())->GetEpsClosure();
  for (auto i{S.begin()}; i != S.end(); i++)
    oldStack.push(*i);
  int count{0};
  while (*c != '\0') {
    count++;
    while (!oldStack.empty()) {
      // std::cout <<"old stack top is: "<<oldStack.top()<<"\t and the state type is: ";

        auto mapItr = 
            NFAObject->GetStates()[oldStack.top()]->GetnonEpsClosure().find(std::string(1,*c));
        if(mapItr != NFAObject->GetStates()[oldStack.top()]->GetnonEpsClosure().end()){
            auto setItr = mapItr->second;
            for (auto j{setItr.begin()}; j != setItr.end(); j++) {
                if (!alreadyOn[*j])
                    addState(*j);
            }
        }
        oldStack.pop();
    }

    while (!newStack.empty()) {
        oldStack.push(newStack.top());
        auto k = oldStack.top();
        StateType temp;
        // std::cout << "state number on the new Stack: "<<k<<std::endl;
        for(auto i:NFAObject->GetStates()){
          if(i->getStateNumber() == k){
              temp = i->GetStateType();
              std::cout << "\n\nThe current charachter is: "<< *c<<"\nThe following NFA has accepting state: " <<std::endl;
              NFAObject->PrintNFAType();
          }
            
        }
        
        if (temp == StateType::ACCEPTING){
            lexemeSize = count >= lexemeSize ? count : lexemeSize;
            
        }
        alreadyOn[newStack.top()] = false;
        newStack.pop();
    }
    c++;
    
  }

  while (!oldStack.empty()) {
    auto k = oldStack.top();
    oldStack.pop();
    StateType temp = NFAObject->GetStates().at(k)->GetStateType();
    std::string str;
    if (temp == StateType::START)
      str = "START";

    if (temp == StateType::ACCEPTING)
      str = "ACCEPTING";

    if (temp == StateType::TRANSITION)
      str = "TRANSITION";

    // if (NFAObject->GetStates().at(k)->GetStateType() == StateType::ACCEPTING)
    //   return true;
  }
}
