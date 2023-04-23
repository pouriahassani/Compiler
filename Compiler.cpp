#include <iostream>
#include "Lexical_analyzer.h"
#include "Parser.h"
#include "NFA.h"
#include <fstream>
#include "NFA_Simulation.h"
#include "RegularExpressionOperations.h"
#include <string>
int main(){
    std::string symbols{"0 1 2 3 4 5 6 7 8 9"};
    // NFA leftNfa{symbols};
    // NFA rightNfa{symbols};
    std::string symbolsa = "a";
    std::string symbolsb = "b";
    NFA singleSumnolL(symbolsa,1);
    NFA singleSumnolR(symbolsb,1);
    NFA singleSumnolLa1(symbolsa,1);
    NFA singleSumnolRb1(symbolsb,1);
    NFA singleSumnolRb2(symbolsb,1);
    NFA* UNFA;
    NFA* INFA;
    NFA* CNFA;
    NFA* CNFA1;
    NFA* CNFA2;
    RegularExpressionOperations REO{};
    UNFA = REO.UnionsOperation(singleSumnolL,singleSumnolR);
    std::cout << "*******\n\n*******"<<std::endl;
    INFA = REO.IterationOperation(*UNFA);
    CNFA = REO.ConcatOperation(singleSumnolLa1,singleSumnolRb1);
    CNFA1 = REO.ConcatOperation(*INFA,*CNFA);
    std::cout << "*******\n\n*******"<<std::endl;
    CNFA2 = REO.ConcatOperation(*CNFA1,singleSumnolRb2);
    // REO.UnionsOperation(singleSumnolL,singleSumnolR);
    // singleSumnolL.PrintNFA();
    // singleSumnolR.PrintNFA();
    std::cout << "*******\n\n*******"<<std::endl;
    // REO.ConcatOperation(singleSumnolL,singleSumnolR);
    // REO.IterationOperation(singleSumnolL);

    // NFASimulation NFAsimlate{&nfa};
    // bool i{NFAsimlate.Simulation("2342")};
    // std::cout << "Is NFA Accepting: "<<i<<std::endl;
    return 0;
}