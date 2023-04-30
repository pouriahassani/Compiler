#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <iostream>
#include <map>
#include <set>
#include <string>
#include<vector>
#include "./../Lexical_Analyzer/NFA.h"
#include "Symbol.h"

// Class Grammar defines the set of productions and the terminals
// of the Grammar
class Grammar {
public:
  Grammar();
  std::string &GetStartSymbol() const;
  std::map<std::string, std::set<std::vector<Symbol>>> &GetProductions() const;
  std::map<NFAType, bool> &GetValidTerminalsMap() const;

  void SetStartSymbol();
  void AddProduction();
  void AddValidTerminal(const NFAType &terminal);

private:
  std::map<std::string, std::set<std::vector<Symbol>>> productions;

  // This map data structure keeps a bool value
  //  for each terminal that is used in the grammar
  std::map<NFAType, bool> validTerminalsMap;

  // Start symbol of the grammar
  std::string startSymbol;
};

#endif
