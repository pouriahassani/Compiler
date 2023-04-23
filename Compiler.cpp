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
    NFA digit1{symbols};
    NFA digitd2{symbols};
    NFA digitd3{symbols};
    NFA digitdDots{symbols};
    NFA digitdOneInstance{symbols};
    NFA digitdCn1{symbols};
    NFA digitdCn2{symbols};
    

    RegularExpressionOperations REO{};
    REO.UnionsOperation(leftNfa,rightNfa);
    singleSumnolL.PrintNFA();
    singleSumnolR.PrintNFA();
    std::cout << "*******\n\n*******"<<std::endl;
    REO.ConcatOperation(singleSumnolL,singleSumnolR);
    REO.IterationOperation(singleSumnolL);

    // NFASimulation NFAsimlate{&nfa};
    // bool i{NFAsimlate.Simulation("2342")};
    // std::cout << "Is NFA Accepting: "<<i<<std::endl;
    return 0;
}