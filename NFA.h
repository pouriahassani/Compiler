#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#ifndef NFA_H
#define NFA_H
// In class NFA there are methods and data member defining the functionality of
// the NFA representation of the regular expressions. The method can simulate
// the NFA structure and define if a sring is matching with the expressed
// regular expression with NFA object

class State {
public:
  State(int state_number);
  void AddEpsEdge(int nextState);
  void AddEdge(std::string edge, int nextState);
  const int getStateNumber();
  const std::unordered_map<int, std::string>& GetnonEpsClosureNextStates();
  const std::vector<int> &GetepsClosureStates();

private:
  int stateNumber;
  std::unordered_map<int, std::string> nonEpsClosureNextStates;
  std::vector<int> epsClosureStates;
};

class NFA {
public:
  NFA(int numberOfStates);
  void CreateNFA(std::ifstream &edgesStatesFile);
  const std::vector<State *>& GetStates();
  const void PrintNFA();



private:
  std::vector<State *> States;
  int numberOfStates;
};

#endif