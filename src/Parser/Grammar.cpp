#include "Grammar.h"
#include "./../Utils/Utils.h"
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

// Basic constructor to just set the name of the grammar
Grammar::Grammar(std::string grammarName) : grammarName(grammarName) {
  eps = new Symbol();
  // TerminalType newNFA = TerminalType::ID;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::IF;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::ELSE;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::GT;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::LT;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::LP;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::RP;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::NUMBER;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::EQ;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::WS;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::INT;
  // validTerminalsMap[newNFA] = false;
  // newNFA = TerminalType::SC;
  // validTerminalsMap[newNFA] = false;
};

void Grammar::CreateGrammar(std::ifstream grammarFileDscr) {

  std::string strline{""};

  while (strline != "End_Grammar") {
    std::getline(grammarFileDscr, strline);
    if (strline == "")
      continue;
    std::stringstream line{strline};
    // std::string
  }
}

void Grammar::SetStartSymbol(std::string str) { startSymbol = str; }

const std::string &Grammar::GetStartSymbol() const { return startSymbol; }

Symbol *Grammar::GetEps() const { return eps; }

const std::unordered_map<std::string, Symbol *>
Grammar::GetNonTerminal() const {
  return nonTerminals;
}

const std::unordered_map<std::string, Symbol *> Grammar::GetTerminals() const {
  return terminals;
}

void Grammar::AddProduction(Symbol *LHS, std::vector<Symbol *> newProduction) {
  productions[LHS].push_back(newProduction);
}

void Grammar::AddTerminal(std::string str) {
  TerminalType newTerminal;
  try {
    newTerminal = StrToNFA(str);
  } catch (InvalidTerminalName &InvalidTerminalName) {
    std::cout << "Error: " << InvalidTerminalName.what() << std::endl;
  }

  try {
    Symbol *newSymbol = new Symbol{newTerminal};
    terminals[str] = newSymbol;
  } catch (const std::exception &e) {
    std::cerr << "Error adding terminal: " << e.what() << std::endl;
  }
}

Symbol *Grammar::AddNonTerminal(std::string str) {
  try {
    std::vector<std::vector<Symbol *>> newRightHandSide;
    Symbol *LHD = new Symbol{str};
    nonTerminals[str] = LHD;
    productions[LHD] = newRightHandSide;
    return LHD;
  } catch (const std::exception &e) {
    std::cerr << "Error adding non-terminal: " << str << e.what() << std::endl;
  }
  return NULL;
}
/*
For find the first of a symbol three rules are applied:
1. if symbol is a terminal, the the first of the symbol is
the symbol itself
if the symbol is a non terminal do following:
2. if A->B is a production, then first(B) is a subset of
first(A) except Epsilon
3. if A->BC is a productoin, and Epsilon belong to first(B),
first of C is a subset of first(A). Morover, is Epsilon is
in first(C), Eplsilon is a member of first(A)
*/
std::set<Symbol *> Grammar::FindFirst(Symbol *symbol) {
  if (symbol->IsTerminal()) {
    symbol->AddFirstOf(symbol);
    return symbol->GetFirstOf();
  }

  if (symbol->IsEps()) {
    symbol->AddFirstOf(symbol);
    return symbol->GetFirstOf();
  }

  for (auto i : productions.at(symbol)) {
    for (auto j = i.begin(); j != i.end(); j++) {
      if ((*j)->IsTerminal()) {
        (*j)->AddFirstOf(*j);
        symbol->AddFirstOf(*j);
        break;
      } else {
        if (j + 1 == i.end()) {
          for (auto k : FindFirst(*j)) {
            symbol->AddFirstOf(k);
          }
        } else {
          bool hasEps = false;
          for (auto k : FindFirst(*j)) {
            if (k->IsEps()) {
              hasEps = true;
              continue;
            }

            symbol->AddFirstOf(k);
          }
          if (!hasEps)
            break;
        }
      }
    }
  }
  return symbol->GetFirstOf();
}

/*
For find the follow of a symbol follwong rules are applied:
1. if A->BC is a production, then first(C) is a subset of
follow(B) except Epsilon
2. if A->BCD is a productoin, and Epsilon belong to first(C),
first of D is a subset of follow(B). Morover, is Epsilon is
in first(D) and first(C), follow(A) is a subset of follow(B)
*/
std::set<Symbol *> Grammar::FindFollow(Symbol *symbol) {
  symbol->PrintSymbol();
  std::cout << "\t";
  for (auto i : productions) {
    for (auto j = i.second.begin(); j != i.second.end(); j++) {
      for (auto k = j->begin(); k != j->end(); k++) {
        if (symbol == *k) {
          if (k + 1 == j->end()) {
            for (auto m : FindFollow(i.first)) {
              symbol->AddFollowOf(m);
            }
          }
          for (auto t = k + 1; t != j->end(); t++) {
            if ((*t)->IsTerminal()) {
              symbol->AddFollowOf(*t);
              break;
            }
            bool hasEps = false;
            for (auto m : (*t)->GetFirstOf()) {
              if (m->IsEps()) {
                hasEps = true;
                continue;
              }
              symbol->AddFollowOf(m);
            }
            if (!hasEps)
              break;
            if (t + 1 == j->end()) {
              for (auto m : FindFollow(i.first)) {
                symbol->AddFollowOf(m);
              }
            }
          }
        }
      }
    }
  }
  return symbol->GetFollowOf();
}

void Grammar::PrintGrammar() {
  std::cout << grammarName << std::endl;
  std::cout << "Terminals: ";
  for (auto i : terminals) {
    PrintNFAType(i.second->GetTerminal());
  }
  std::cout << std::endl;
  for (auto i : productions) {
    i.first->PrintSymbol();
    std::cout << "->";
    for (auto j = i.second.begin(); j != i.second.end(); j++) {
      for (auto k : *j)
        k->PrintSymbol();
      if (j + 1 != i.second.end())
        std::cout << '|';
    }
    std::cout << std::endl;
  }
  // The first of non terminals
  std::cout << "The first of non terminals" << std::endl;
  for (auto i : nonTerminals) {
    std::cout << i.first << " ==> ";
    for (auto k : i.second->GetFirstOf()) {
      k->PrintSymbol();
    }
    std::cout << std::endl;
  }

  // The first of non terminals
  std::cout << "\nThe follow of non terminals" << std::endl;
  for (auto i : nonTerminals) {
    std::cout << i.first << " ==> ";
    for (auto k : i.second->GetFollowOf()) {
      k->PrintSymbol();
    }
    std::cout << std::endl;
  }
}