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

  Symbol::Symbol(){
    SetSymbolType(3);
  }


  const TerminalType& Symbol::GetTerminal() const{
    return symbolT;
  }
  const std::string&  Symbol::GetNonTerminal() const{
    return symbolNonT;
  }

  std::set <Symbol*> Symbol::GetFirstOf(){
    return firstOf;
  }

    std::set <Symbol*> Symbol::GetFollowOf(){
    return followOf;
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

  bool Symbol::IsEps(){
    return (symbolType == 3);
  }


  void Symbol::AddFirstOf(Symbol* symbol){
    firstOf.insert(symbol);
  }

  void Symbol::AddFollowOf(Symbol* symbol){
    followOf.insert(symbol);
  }

  void Symbol::PrintSymbol(){
    if(symbolType == 0)
      PrintNFAType(symbolT);
    if(symbolType == 1)
      std::cout << ' ' << symbolNonT << ' ';
    if(symbolType == 2)
      std::cout << " . " << ' ';
    if(symbolType == 3)
      std::cout << " eps " << ' ';
  }