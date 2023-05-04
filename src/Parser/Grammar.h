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
  Grammar(std::string grammarName);
  void CreateGrammar(std::ifstream GrammarFileDscr);
  std::string &GetStartSymbol() const;
  std::map<std::string, std::set<std::vector<Symbol>>> &GetProductions() const;
  std::map<TerminalType, bool> &GetValidTerminalsMap() const;

  void SetStartSymbol(std::string str);
  void AddProduction(std::string str,Symbol newSymbol);
  void AddValidTerminal(std::string str);
  void AddNonTerminal(std::string str);
private:
  std::map<std::string, std::vector<Symbol>> productions;

  // This map data structure keeps a bool value
  //  for each terminal that is used in the grammar
  std::map<TerminalType, bool> validTerminalsMap;

  // Start symbol of the grammar
  std::string startSymbol;

  //Grammar name to distinguish between different grammars   
  std::string grammarName;
};

#endif
