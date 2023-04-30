#include "NFA.h"
#include "Exception.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor for State class
State::State(int stateNumber, StateType stateType)
    : stateNumber(stateNumber), stateType(stateType){};

// Copy Constructor for State class
State::State(const State& stateObject) {
  this->stateNumber = stateObject.stateNumber;
  for (const auto &i : stateObject.GetnonEpsClosure()) {
    for (auto j : i.second)
      this->AddEdge(i.first, j);
  }
  for (const auto &i : stateObject.GetEpsClosure()) {
    this->AddEpsEdge(i);
  }
  this->stateType = stateObject.stateType;
}

// Add epsilon edge to the current state
void State::AddEpsEdge(int nextStateNumber) {
  EpsClosure.insert(nextStateNumber);
}

// Add non-epsilon edge to the current state
void State::AddEdge(std::string edge, int nextStateNumber) {
  nonEpsClosure[edge].insert(nextStateNumber);
}

// Get the state number of the current state
const int &State::GetStateNumber() const { return stateNumber; }

// Get the state type of the current state
const StateType &State::GetStateType() const { return stateType; }

// Set the state type of the current state
void State::SetStateType(StateType stateType) { this->stateType = stateType; }

// Set the state number of the current state
void State::SetStateNumber(int stateNumber) { this->stateNumber = stateNumber; }

// Add a new state to the epsilon closure of the current state
void State::setEpsClosure(int newEps) { EpsClosure.insert(newEps); }

// Increment the state numbers of the current state and its epsilon closure
void State::IncrementStateNumbers(int base) { stateNumber += base; }

// Increment the state numbers of the epsilon closure of the current state
void State::IncrementEpsClosureStateNumbers(int base) {

  std::set<int> tmpSet{EpsClosure};
  EpsClosure.clear();
  for (std::set<int>::iterator i = tmpSet.begin(); i != tmpSet.end(); i++) {
    EpsClosure.insert(*i + base);
  }
}

// Increment the state numbers of the non-epsilon closure of the current state
void State::IncrementNonEpsClosureStateNumbers(int base) {
  for (auto mapItr{nonEpsClosure.begin()}; mapItr != nonEpsClosure.end();
       mapItr++) {
    std::set<int> tmpSet{mapItr->second};
    std::set<int> &tmpSetPtr{mapItr->second};
    tmpSetPtr.clear();
    for (std::set<int>::iterator i = tmpSet.begin(); i != tmpSet.end(); i++) {
      tmpSetPtr.insert(*i + base);
    }
  }
}

// Update all the epsilon closures of the current state for a specific state number change
void State::UpdateEpsFromOldStateNumToNew(int changedStateIdOld, int changedStateIdNew){
  if(EpsClosure.find(changedStateIdOld) != EpsClosure.end()){
    EpsClosure.erase(changedStateIdOld);
    EpsClosure.insert(changedStateIdNew);
  }
}

// Update all the non-epsilon closures of the current state for a specific state number change
void State::UpdateNonEpsFromOldStateNumToNew(int changedStateIdOld, int changedStateIdNew){
   for(auto& i : nonEpsClosure){
    if(i.second.find(changedStateIdOld) != i.second.end()){
      i.second.erase(changedStateIdOld);
      i.second.insert(changedStateIdNew);
    }
  }
}

const std::unordered_map<std::string, std::set<int>> &
State::GetnonEpsClosure() const {
  return nonEpsClosure;
}

const std::set<int> &State::GetEpsClosure() const { return EpsClosure; }

void State::RemoveEpsClosure(int i) { EpsClosure.erase(i); }
void State::RemoveNonEpsClosure(std::string edge, int i) {
  if (nonEpsClosure.find(edge) != nonEpsClosure.end()) {
    const auto &itr = nonEpsClosure.find(edge);
    itr->second.erase(i);
  }
}

void State::PrintState(){
    std::cout <<"state number: "<<GetStateNumber() << ": ";
    PrintStateType();
    std::cout << "epsilon edges:" << GetEpsClosure().size() << std::endl;
    for (auto j{GetEpsClosure().begin()}; j != GetEpsClosure().end();
         j++) {
      std::cout << *j << ", ";
    }
    std::cout << "\n"
              << "non epsilon edges:" << std::endl;
    for (auto j : GetnonEpsClosure()) {
      std::cout << GetStateNumber() << " ==" << j.first << "==> ";
      for (auto k{j.second.begin()}; k != j.second.end(); k++)
        std::cout << *k << ' ';
    }
    std::cout << '\n' << std::endl;
  
}

NFA::NFA(){
  numberOfStates = 0;
}

NFA::NFA(NFA const &NFAObject) {
  for (const auto &i : NFAObject.States) {
    State *newState = new State{*i.second};
    this->States.insert(std::make_pair(i.first, newState));
  }
  this->numberOfStates = NFAObject.numberOfStates;
}

void NFA::SetNFAType(NFAType typeOfNFA) { this->typeOfNFA = typeOfNFA; }
const NFAType& NFA::GetNFAType() const { return typeOfNFA; }

NFA::NFA(std::string const &symbols_, bool isSingleSymbol) {
  std::string symbols = ltrim(rtrim(symbols_));
  numberOfStates = 0;
  std::stringstream symbolsStream{symbols};
  std::string symbol;
  State *startState = new State(0, StateType::START);
  int stateNumbertmp{0};
  States.insert(std::make_pair(stateNumbertmp, startState));

  State *endState = new State(++stateNumbertmp, StateType::ACCEPTING);
  States.insert(std::make_pair(stateNumbertmp, endState));

// Union of single symbol NFAs one big single NFA
  if (isSingleSymbol) {
    symbolsStream >> symbol;
    States[0]->AddEdge(std::string(symbol), 1);
  }

  else {
    while (symbolsStream >> symbol) {
      int leftId{++stateNumbertmp};
      int rightId{++stateNumbertmp};

      State *leftState = new State(leftId, StateType::TRANSITION);
      leftState->AddEdge(symbol, rightId);
      States.insert(std::make_pair(leftId, leftState));
      States[0]->AddEpsEdge(leftId);

      State *rightState = new State(rightId, StateType::TRANSITION);
      States.insert(std::make_pair(rightId, rightState));
      States[rightId]->AddEpsEdge(1);
    }
  }

  numberOfStates = stateNumbertmp + 1;
  // PrintNFA();
}

void State::PrintStateType() {
  if (this->GetStateType() == StateType::ACCEPTING)
    std::cout << "Accepting" << std::endl;

  if (this->GetStateType() == StateType::TRANSITION)
    std::cout << "TRANSITION" << std::endl;

  if (this->GetStateType() == StateType::START)
    std::cout << "START" << std::endl;
}

void NFA::PrintNFAType() {
  if (typeOfNFA == NFAType::ID)
    std::cout << "ID" << std::endl;
  if (typeOfNFA == NFAType::NUMBER)
    std::cout << "NUMBER" << std::endl;
  if (typeOfNFA == NFAType::ELSE)
    std::cout << "ELSE" << std::endl;
  if (typeOfNFA == NFAType::EQ)
    std::cout << "EQ" << std::endl;
  if (typeOfNFA == NFAType::GT)
    std::cout << "GT" << std::endl;
  if (typeOfNFA == NFAType::IF)
    std::cout << "IF" << std::endl;
  if (typeOfNFA == NFAType::INT)
    std::cout << "INT" << std::endl;
  if (typeOfNFA == NFAType::LP)
    std::cout << "LP" << std::endl;
  if (typeOfNFA == NFAType::LT)
    std::cout << "LT" << std::endl;
  if (typeOfNFA == NFAType::RP)
    std::cout << "RP" << std::endl;
  if (typeOfNFA == NFAType::SC)
    std::cout << "SC" << std::endl;
  if (typeOfNFA == NFAType::WS)
    std::cout << "WS" << std::endl;
}

void PrintNFAType(NFAType typeOfNFA){
  if (typeOfNFA == NFAType::ID)
    std::cout << "ID" << std::endl;
  if (typeOfNFA == NFAType::NUMBER)
    std::cout << "NUMBER" << std::endl;
  if (typeOfNFA == NFAType::ELSE)
    std::cout << "ELSE" << std::endl;
  if (typeOfNFA == NFAType::EQ)
    std::cout << "EQ" << std::endl;
  if (typeOfNFA == NFAType::GT)
    std::cout << "GT" << std::endl;
  if (typeOfNFA == NFAType::IF)
    std::cout << "IF" << std::endl;
  if (typeOfNFA == NFAType::INT)
    std::cout << "INT" << std::endl;
  if (typeOfNFA == NFAType::LP)
    std::cout << "LP" << std::endl;
  if (typeOfNFA == NFAType::LT)
    std::cout << "LT" << std::endl;
  if (typeOfNFA == NFAType::RP)
    std::cout << "RP" << std::endl;
  if (typeOfNFA == NFAType::SC)
    std::cout << "SC" << std::endl;
  if (typeOfNFA == NFAType::WS)
    std::cout << "WS" << std::endl;
}

void NFA::PrintNFA() const {
  std::cout << "NFA size" << States.size() << std::endl;
  for (auto i : States) {
    std::cout << "key: "<<i.first<<"\tstate number: "<<i.second->GetStateNumber() << ": ";
    i.second->PrintStateType();
    std::cout << "epsilon edges:" << i.second->GetEpsClosure().size() << std::endl;
    for (auto j{i.second->GetEpsClosure().begin()}; j != i.second->GetEpsClosure().end();
         j++) {
      std::cout << *j << ", ";
    }
    std::cout << "\n"
              << "non epsilon edges:" << std::endl;
    for (auto j : i.second->GetnonEpsClosure()) {
      std::cout << i.second->GetStateNumber() << " ==" << j.first << "==> ";
      for (auto k{j.second.begin()}; k != j.second.end(); k++)
        std::cout << *k << ' ';
    }
    std::cout << '\n' << std::endl;
  }
}

const std::map<int,State *> &NFA::GetStates() const{ return States; }
int NFA::GetNumberOfStates() const{ return numberOfStates; };
