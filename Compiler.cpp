#include <iostream>
#include "Lexical_analyzer.h"
#include "Parser.h"
#include "NFA.h"
#include <fstream>
#include "NFA_Simulation.h"
#include <string>
int main(){
    std::string symbols{"0 1 2 3 4 5 6 7 8 9"};
    NFA nfa{symbols};
    NFASimulation NFAsimlate{&nfa};
    bool i{NFAsimlate.Simulation("2342")};
    std::cout << "Is NFA Accepting: "<<i<<std::endl;
    return 0;
}