
#include "NFA.h"
#include "Exception.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Utils.h"

State::State(int stateNumber,StateType stateType) : stateNumber(stateNumber), stateType(stateType){};

void State::AddEpsEdge(int nextStateNumber) {
  EpsClosure.insert(nextStateNumber);
}

void State::AddEdge(std::string edge, int nextStateNumber) {
  nonEpsClosure[edge].insert(nextStateNumber);
}

const int State::getStateNumber() { return stateNumber; }

const StateType &State::GetStateType() { return stateType; }

void State::SetStateType(StateType stateType) { this->stateType = stateType; }

void State::SetStateNumber(int stateNumber){
  this->stateNumber = stateNumber; 
}

void State::setEpsClosure(int newEps){
  EpsClosure.insert(newEps);
}


void State::IncrementStateNumbers(int base){
  stateNumber += base;
}

void State::IncrementEpsClosureStateNumbers(int base){

  std::set<int> tmpSet{EpsClosure};
  EpsClosure.clear();
  for(std::set<int>::iterator i = tmpSet.begin() ; i != tmpSet.end() ; i++){
    EpsClosure.insert(*i + base);
  }
}

void State::IncrementNonEpsClosureStateNumbers(int base){
  for(auto mapItr{nonEpsClosure.begin()} ; mapItr != nonEpsClosure.end() ; mapItr++){
    std::set<int> tmpSet{mapItr->second};
    std::set<int>& tmpSetPtr{mapItr->second};
    tmpSetPtr.clear();
    for(std::set<int>::iterator i = tmpSet.begin() ; i != tmpSet.end() ; i++){
      tmpSetPtr.insert(*i + base);
    }
  }
}

const std::unordered_map<std::string, std::set<int>> &
                    State::GetnonEpsClosure() {
  return nonEpsClosure;
}

const std::set<int> &State::GetEpsClosure() {
  return EpsClosure;
}

NFA::NFA(std::string& symbols,bool isSingleSymbol) {
  symbols = ltrim(rtrim(symbols));
  numberOfStates = 0;
  std::stringstream symbolsStream{symbols};
  std::string symbol;
  State *startState = new State(0, StateType::START);
  int stateNumbertmp{0};
  startState->SetStateType(StateType::START);
  States.push_back(startState);

  State *endState = new State(++stateNumbertmp, StateType::ACCEPTING);
  endState->SetStateType(StateType::ACCEPTING);
  States.push_back(endState);

  if(isSingleSymbol){
    symbolsStream >> symbol;
    States[0]->AddEdge(std::string(symbol),1);
  }

  else{
    while(symbolsStream >> symbol) {
      int leftId{++stateNumbertmp};
      int rightId{++stateNumbertmp};

      State *leftState = new State(leftId, StateType::TRANSITION);
      leftState->AddEdge(symbol,rightId);
      leftState->SetStateType(StateType::TRANSITION);
      States.push_back(leftState); 
      States[0]->AddEpsEdge(leftId);

      State *rightState = new State(rightId,StateType::TRANSITION);
      rightState->SetStateType(StateType::TRANSITION);
      States.push_back(rightState);
      States[rightId]->AddEpsEdge(1);    
    }
  }

  numberOfStates = stateNumbertmp+1;
  // PrintNFA();
}


const void NFA::PrintNFA() {
  std::cout <<"Vector size"<< States.size()<<std::endl;
  for (auto i : States) {
    std::cout << i->getStateNumber() << ": " ;
    if(i->GetStateType() == StateType::ACCEPTING)
      std::cout << "ACCEPTING"<<std::endl;
    if(i->GetStateType() == StateType::START)
      std::cout << "START"<<std::endl;
    if(i->GetStateType() == StateType::TRANSITION)
      std::cout << "TRANSITION"<<std::endl;
    std::cout << "epsilon edges:" <<  i->GetEpsClosure().size() << std::endl;
    for (auto j{i->GetEpsClosure().begin()} ; j != i->GetEpsClosure().end() ; j++) {
      std::cout << *j << ", ";
    }
    std::cout << "\n"
              << "non epsilon edges:" << std::endl;
    for (auto j : i->GetnonEpsClosure()) {
        std::cout << i->getStateNumber()<< " ==" << j.first <<"==> ";
        for(auto k{j.second.begin()} ;k != j.second.end() ; k++)
            std::cout << *k << ' ';
    }
    std::cout << '\n' <<std::endl;
  }
}

const std::vector<State *> &NFA::GetStates() { return States; }
const int NFA::GetNumberOfStates(){
    return numberOfStates;
};
