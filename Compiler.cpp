#include <iostream>
#include "Lexical_analyzer.h"
#include "Parser.h"
#include "NFA.h"
#include <fstream>

int main(){
    std::ifstream file_;
    file_.open("NFAFile");
    std::string numberOfStates;
    std::getline(file_,numberOfStates);
    NFA nfa{stoi(numberOfStates)};
    nfa.CreateNFA(file_);
    return 0;
}