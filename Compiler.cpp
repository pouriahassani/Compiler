#include <iostream>
#include "Lexical_analyzer.h"
#include "Parser.h"
#include "NFA.h"
#include <fstream>
#include "NFA_Simulation.h"
int main(){
    NFA nfa{"NFAFile"};
    nfa.CreateNFA();
    NFASimulation NFAsimlate{&nfa};
    bool i{NFAsimlate.Simulation("2342")};
    std::cout << "Is NFA Accepting: "<<i<<std::endl;
    return 0;
}