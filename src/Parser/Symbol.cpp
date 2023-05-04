#include "Symbol.h"



  Symbol::Symbol(TerminalType symbolT) : symbolT(symbolT){
    SetSymbolType(0);
  }
  Symbol::Symbol(std::string symbolNonT) : symbolNonT(symbolNonT){
    SetSymbolType(1);
  }
  Symbol::Symbol(char symbolDot) : symbolDot(symbolDot){
    SetSymbolType(2);
  }

  const TerminalType& Symbol::GetTerminal() const{
    return symbolT;
  }
  const std::string&  Symbol::GetNonTerminal() const{
    return symbolNonT;
  }

  void  Symbol::SetSymbolType(int symbolType){
    this->symbolType = symbolType;
  }

  bool  Symbol::IsDot(){
    return (symbolType == 2);
  }
  bool  Symbol::IsTerminal(){
    return (symbolType == 0);
  }
  bool  Symbol::IsNonTerminal(){
    return (symbolType == 1);
  }