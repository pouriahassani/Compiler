
#include "NFA_Simulation.h"
#include "NFA.h"
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

NFASimulation::NFASimulation(NFA *NFAObject) : NFAObject(NFAObject) {
  int maxstateNum = NFAObject->GetStates().size();
  
  alreadyOn.resize(maxstateNum, false);
}

NFA* NFASimulation::GetNFAOBject(){return NFAObject;}

// std::set<int> &NFASimulation::Move(std::set<int> &S, char c) {
//   std::string C;
//   C = std::string(1, c);
//   std::set<int> returnStatesSet;
//   for (auto i{S.begin()}; i != S.end(); i++) {
//     int statId = *i;
//     State *nxtState{NFAObject->GetStates().at[statId]};
//     for (int j{0}; j < nxtState->GetnonEpsClosure().size(); j++) {
//       if (nxtState->GetnonEpsClosure().find(C) !=
//           nxtState->GetnonEpsClosure().end()) {
//         auto pairItr{*(nxtState->GetnonEpsClosure().find(C))};
//         std::set<int> setItr{pairItr.second};
//         for (auto k{setItr.begin()}; k != setItr.end(); k++)
//           returnStatesSet.insert(*k);
//       }
//     }
//   }
//   S = returnStatesSet;
//   return S;
// }



// std::set<int> &NFASimulation::Eclosure(std::set<int> &S) {
//   std::set<int> returnStatesSet;
//   for (auto i{S.begin()}; i != S.end(); i++){
//     alreadyOn[*i] = true;
//     oldStack.push(*i);
//   }
//   while (!oldStack.empty()) {
//     std::set<int> setItr{
//         NFAObject->GetStates()[oldStack.top()]->GetEpsClosure()};
//     for (auto j{setItr.begin()}; j != setItr.end(); j++) {
//       if (!alreadyOn[*j])
//         addState(*j);
//       oldStack.pop();
//     }
//   }

//   while (!newStack.empty()) {
//     oldStack.push(newStack.top());
//     alreadyOn[newStack.top()] = false;
//     returnStatesSet.insert(newStack.top());
//     newStack.pop();
//   }
//   S = returnStatesSet;
//   return S;
// }

void NFASimulation::addState(int stateNumber) {
  newStack.push(stateNumber);
  alreadyOn[stateNumber] = true;
  for (auto i{NFAObject->GetStates().at(stateNumber)->GetEpsClosure().begin()};
       i != NFAObject->GetStates().at(stateNumber)->GetEpsClosure().end(); i++) {
    if (!alreadyOn[*i])
      addState(*i);
  }
}

void NFASimulation::Simulation(std::string line,int& lexemeSize) {
 
  auto c = line.begin();
  lexemeSize = 0;

  //Push the start state to the oldStack 
  for(auto i:NFAObject->GetStates())
    if(i.second->GetStateType() == StateType::START)
      oldStack.push(i.first);
  
  // Push all the epsilon states reachable from the start state to the newStack
  addState(oldStack.top());

  // Push all the epsilon states reachable from the start state to the oldStack
  // and empty newStack and set all the elements in the alreadyOn vector to false
  while (!newStack.empty()) {
        oldStack.push(newStack.top());
        auto k = oldStack.top();
        alreadyOn[k] = false;
        newStack.pop();
  }

  int count{0};
  while (*c != '\0') {
    count++;
    // Go throught all the states reached so far and check if the push all the states that are
    // reachable from current reached states to the newStack
    while (!oldStack.empty()) {
        auto mapItr = 
            NFAObject->GetStates().at(oldStack.top())->GetnonEpsClosure().find(std::string(1,*c));
        if(mapItr != NFAObject->GetStates().at(oldStack.top())->GetnonEpsClosure().end()){
            auto setItr = mapItr->second;
            for (auto j{setItr.begin()}; j != setItr.end(); j++) {
                if (!alreadyOn[*j])
                    addState(*j);
            }
        }
        oldStack.pop();
    }
    //Chceck if we the accepting state is in the current set of reached states
    // and uf there is an accepting state, set the longest accepetable lexeme 
    while (!newStack.empty()) {
        oldStack.push(newStack.top());
        auto k = oldStack.top();
        StateType temp = NFAObject->GetStates().at(k)->GetStateType();
       
        if (temp == StateType::ACCEPTING){
            lexemeSize = count >= lexemeSize ? count : lexemeSize;
        }
        alreadyOn[newStack.top()] = false;
        newStack.pop();
    }
    c++;
  }

// Empty oldStack to be ready for the next lexeme evaluation
  while (!oldStack.empty()) {
    auto k = oldStack.top();
    oldStack.pop();
  }
}
