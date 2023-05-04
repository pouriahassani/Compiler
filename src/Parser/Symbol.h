#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include "./../Lexical_Analyzer/NFA.h"
#define TerminalType NFAType
// class Symbol defines one symbol in one right handside
// of a production. This symbol can be either a termial or a non-terminal or a
// '.'

class Symbol {
public:
  Symbol(TerminalType symbolT);
  Symbol(std::string symbolNonT);
  Symbol(char symbolDot);

  const TerminalType& GetTerminal() const;
  const std::string& GetNonTerminal() const;
  void SetSymbolType(int symbolType);
  void PrintSymbol();
  bool IsDot();
  bool IsTerminal();
  bool IsNonTerminal();

private:
  TerminalType symbolT;
  std::string symbolNonT;
  char symbolDot;

  // if the symbolType is 0 the symbol is terminal
  // if the symbolType is 1 the symbol is nonterminal
  // if the symbolType is 2 the symbol is dot 
  int symbolType;
};



#endif