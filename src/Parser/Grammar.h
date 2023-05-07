#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <iostream>
#include <map>
#include <set>
#include <string>
#include<vector>
#include<unordered_map>
#include "./../Lexical_Analyzer/NFA.h"
#include "Symbol.h"

// Class Grammar defines the set of productions and the terminals
// of the Grammar
class Grammar {
public:
  Grammar(std::string grammarName);
  void CreateGrammar(std::ifstream GrammarFileDscr);
  const std::string &GetStartSymbol() const;
  Symbol* GetEps() const;
  std::map<std::string, std::set<std::vector<Symbol>>> &GetProductions() const;
  void SetStartSymbol(std::string str);
  void AddProduction(Symbol* LHS,std::vector<Symbol*>newProduction);
  const std::unordered_map<std::string , Symbol*> GetNonTerminal() const;
  const std::unordered_map<std::string ,Symbol *> GetTerminals() const;
  void AddTerminal(std::string str);
  Symbol*  AddNonTerminal(std::string str);
  void PrintGrammar();
  std::set<Symbol*> FindFirst(Symbol* symbol);
  std::set<Symbol*> FindFollow(Symbol* symbol);
private:
  std::map<Symbol*, std::vector<std::vector<Symbol*>>> productions;

  // This map data structure keeps a bool value
  //  for each terminal that is used in the grammar
  std::unordered_map<std::string, Symbol*> terminals;

  // Nonterminal pointers
  std::unordered_map<std::string,Symbol*> nonTerminals;

  // Start symbol of the grammar
  std::string startSymbol;

  //Grammar name to distinguish between different grammars   
  std::string grammarName;

  // Add an Epsilon symbol as well
  Symbol* eps;
};

#endif
