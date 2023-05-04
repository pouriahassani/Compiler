#ifndef NFA_H
#define NFA_H

#include "./../Utils/Utils.h"
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

// In class NFA there are  methods and data member defining the functionality of
// the NFA representation of the regular expressions. The method can simulate
// the NFA structure and define if a sring is matching with the expressed
// regular expression with NFA object

enum class NFAType { ID, NUMBER, IF, ELSE, INT, LP, RP, LT, GT, EQ, SC, WS, NON };
extern int number_of_unique_tokens;
// Convert the string seen in the input and find the corresponding NFAType
NFAType StrToNFA(std::string str);

// Class State represents a state in the NFA
// Each state object hold a a set of pointers to the epsilon closure states of
// the current state and a map with key to be the edge which in turn is a symbol
// and the value to be a set of pointers to the state that his state can reach
// with that specific key
class State {
public:
  State(int state_number, StateType stateType);
  State(const State& stateObject);
  void AddEpsEdge(int nextState);
  void AddEdge(std::string edge, int nextState);
  const int& GetStateNumber() const;
  const std::unordered_map<std::string, std::set<int>> &
  GetnonEpsClosure() const;
  const std::set<int> &GetEpsClosure() const;
  const StateType &GetStateType() const;
  void SetStateType(StateType stateType);
  void SetStateNumber(int stateNumber);
  void setEpsClosure(int newEps);
  void RemoveEpsClosure(int i);
  void RemoveNonEpsClosure(std::string edge, int i);
  void PrintState();
  // Updates all the epsilon closure of this state for a specific State number change
  void UpdateEpsFromOldStateNumToNew(int changedStateIdOld, int changedStateIdNew);

  // Updates all the non epsilon closure of this state for a specific State number change
  void UpdateNonEpsFromOldStateNumToNew(int changedStateIdOld, int changedStateIdNew);

  void IncrementStateNumbers(int base);
  void IncrementEpsClosureStateNumbers(int base);
  void IncrementNonEpsClosureStateNumbers(int base);
  void PrintStateType();

private:
  int stateNumber;
  std::unordered_map<std::string, std::set<int>> nonEpsClosure;
  std::set<int> EpsClosure;
  StateType stateType;
};

// Class NFA is the graph with nodes to be states and edges to be either epsilon or symbols
// The map statenumberToStatePtr is mapping the state number to the pointer of that state
class NFA {
public:
  NFA();
  NFA(std::string const &symbols, bool isSingleSymbol = true);
  NFA(NFA const &NFAObject);
  
  const std::map<int ,State*> &GetStates()const;
  void PrintNFA() const;
  int GetNumberOfStates()const;
  void IncrementStateNumbers(int base);
  const NFAType& GetNFAType() const;
  void SetNFAType(NFAType typeOfNFA);
  void PrintNFAType();

private:
  std::map<int,State *> States;
  int numberOfStates;
  friend class RegularExpressionOperations;
  NFAType typeOfNFA;
};

void PrintNFAType(NFAType);
#endif