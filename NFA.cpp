
#include "NFA.h"
#include "Exception.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Utils.h"


State::State(int stateNumber) { this->stateNumber = stateNumber; }

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

NFA::NFA(std::string NFAFileName) : NFAFileName(NFAFileName) {
  std::ifstream NFAFile;
  NFAFile.open(NFAFileName);
  std::string S;
  std::getline(NFAFile,S);
  S = ltrim(rtrim(S));
  std::stringstream line(S);
  std::string numberOfStates;
  line >> numberOfStates;
  this->numberOfStates = stoi(numberOfStates);
  for (int i{0}; i < this->numberOfStates; i++) {
    State *newState = new State(i);
    States.push_back(newState);
  }
  NFAFile.close();
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
}
void NFA::CreateNFA() {
  std::string edge;
  std::string currStateNumber;
  std::string nextStateNumber;
  std::string isEps;
  std::string S;
  std::string StatType;
  std::ifstream edgesStatesFile;
  edgesStatesFile.open(NFAFileName);
  int stateCount{0};
  std::getline(edgesStatesFile, S);
  while (stateCount < numberOfStates) {
    std::string stateNumberFromFile;
    std::string stateTypeFromFile;
    std::getline(edgesStatesFile, S);
    S = ltrim(rtrim(S));
    // std::cout << stateCount<<' '<<S << std::endl;
    if (S == "")
      continue;
    // std::cout << S<<std::endl;
    stateCount++;
    std::stringstream line(S);
    line >> stateTypeFromFile;
    line >> stateNumberFromFile;
    int stateId = stoi(stateNumberFromFile);
    StateType currStateType{AssignStateType(stoi(stateTypeFromFile))};
    States[stateId]->SetStateType(currStateType);
  }

  while (std::getline(edgesStatesFile, S)) {
    S = ltrim(rtrim(S));
    // std::cout << S << std::endl;
    if (S == "")
      continue;

    std::stringstream line(S);
    line >> isEps;
    line >> currStateNumber;
    line >> nextStateNumber;

    if (stoi(isEps) == 0) {
      if (!(line >> edge))
        throw FileReadException{};
    }

    if (stoi(isEps) == 0)
      States[stoi(currStateNumber)]->AddEdge(edge, stoi(nextStateNumber));
    else
      States[stoi(currStateNumber)]->AddEpsEdge(stoi(nextStateNumber));
  }
//   PrintNFA();
  edgesStatesFile.close();
}
