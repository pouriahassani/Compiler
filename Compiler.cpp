#include <iostream>
#include "Lexical_analyzer.h"
#include "Parser.h"
#include "NFA.h"
#include <fstream>
#include "NFA_Simulation.h"
#include "RegularExpressionOperations.h"
#include <string>
int main(){
    Lexical_analyzer lex;
    std::string fileName;
    fileName = "source_program.cpp";
    lex.Analyze(fileName);
    lex.PrintTokenList();
   return 0;
}