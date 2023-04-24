#ifndef NFA_H
#define NFA_H

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include "Utils.h"


// In class NFA there are methods and data member defining the functionality of
// the NFA representation of the regular expressions. The method can simulate
// the NFA structure and define if a sring is matching with the expressed
// regular expression with NFA object



class State {
public:
  State(int state_number, StateType stateType);
  State(State &stateObject);
  void AddEpsEdge(int nextState);
  void AddEdge(std::string edge, int nextState);
  const int getStateNumber();
  const std::unordered_map<std::string , std::set<int>>& GetnonEpsClosure();
  const std::set<int> &GetEpsClosure();
  const StateType& GetStateType();
  void SetStateType(StateType stateType);
  void SetStateNumber(int stateNumber);
  void setEpsClosure(int newEps);

  void IncrementStateNumbers(int base);
  void IncrementEpsClosureStateNumbers(int base);
  void IncrementNonEpsClosureStateNumbers(int base);

private:
  int stateNumber;
  std::unordered_map<std::string , std::set<int>> nonEpsClosure;
  std::set<int> EpsClosure;
  StateType stateType;
};

class NFA {
public:
  NFA(std::string& symbols , bool isSingleSymbol = true);
  NFA(NFA& NFAObject);
  const std::vector<State *>& GetStates();
  const void PrintNFA();
  const int GetNumberOfStates();
  void IncrementStateNumbers(int base);


private:
  std::vector<State *> States;
  int numberOfStates;
  std::string NFAFileName;
  friend class RegularExpressionOperations;
};

#endif