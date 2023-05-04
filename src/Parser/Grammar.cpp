#include "Grammar.h"
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include "./../Utils/Utils.h"

// Basic constructor to just set the name of the grammar
Grammar::Grammar(std::string grammarName)
: grammarName(grammarName){
  TerminalType newNFA = TerminalType::ID;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::IF;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::ELSE;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::GT;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::LT;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::LP;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::RP;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::NUMBER;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::EQ;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::WS;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::INT;
  validTerminalsMap[newNFA] = false;
  newNFA = TerminalType::SC;
  validTerminalsMap[newNFA] = false;
};

/* Creates the grammar using the the ifstream GrammarFileDscr
 first the name of the grammar is written in the file and then the 
 terminal and non terminals are listed with each list in one line
 later the production for each non terminal is listed line by line.
 end of grammar is detected by line written as "End Grammar"*/
void Grammar::CreateGrammar(std::ifstream grammarFileDscr){

  std::string strline{""};

  while (strline != "End_Grammar"){
    std::getline(grammarFileDscr,strline);
    if(strline == "")
        continue;
    std::stringstream line{strline};
    // std::string 
  }
}

void Grammar::SetStartSymbol(std::string str){
  startSymbol = str;
}

void Grammar::AddProduction(std::string str,Symbol newSymbol){
  productions[str].push_back(newSymbol);
}

void Grammar::AddValidTerminal(std::string str){
  TerminalType newTerminal;
  try{
    newTerminal = StrToNFA(str);
  }
  catch(InvalidTerminalName& InvalidTerminalName){
    std::cout << "Error: " << InvalidTerminalName.what()<<std::endl;
  }
  validTerminalsMap[newTerminal] = true;
}

void Grammar::AddNonTerminal(std::string str){
  std::vector<Symbol> newRightHandSide;
  productions[str] = newRightHandSide;
}