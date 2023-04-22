
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

const std::unordered_map<std::string, std::set<int>> &
                    State::GetnonEpsClosure() {
  return nonEpsClosure;
}

const std::set<int> &State::GetEpsClosure() {
  return EpsClosure;
}

NFA::NFA(std::string& symbols) {
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


  numberOfStates = stateNumbertmp;
  // PrintNFA();
}

const void NFA::PrintNFA() {
  for (auto i : States) {
    std::cout << i->getStateNumber() << ": " << std::endl;
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
