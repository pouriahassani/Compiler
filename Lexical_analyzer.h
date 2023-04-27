// This the header file for the lexical analyzer
// In this file there are classes defineing the lecical analyzer's
// functionalities The description of each class is given on top of the class
// decleration

#ifndef LEXYCAL_ANALYZER
#define LEXYCAL_ANALYZER
#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <fstream>
#include <vector>
#include <iostream>
#include "NFA.h"
#include "RegularExpressionOperations.h"
#include "NFA_Simulation.h"

class SymbolTable {
public:
private:
};

class ReturnTokenAttribute {
public:
  ReturnTokenAttribute();
  std::string IDvalue;
  SymbolTable *symbolTablePtr;
  bool noValue;
};

class Lexical_analyzer {
public:
  Lexical_analyzer();
  void ExtractTokens();
  void CreateNFAGraphs();
  void Analyze(std::string  fileName);
  void GetlongestNFAName(NFASimulation *NFASim, int& LongestNFASize);
  void PrintTokenList()const;

private:
  std::vector<std::pair<NFAType,ReturnTokenAttribute>>TokenList;
  char *forwardPtr;
  char *lexemeBeginPtr;
  std::string line;
  std::vector<NFA*>NFAGraphs;
};

#endif
