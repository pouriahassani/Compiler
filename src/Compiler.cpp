#include <iostream>
#include "Lexical_analyzer.h"
#include "Parser.h"
#include "NFA.h"
#include <fstream>
#include "NFA_Simulation.h"
#include "RegularExpressionOperations.h"
#include <string>
int main(int argc, char **argv){
    if(argc < 2){
        std::cout << "Error: fileName to be compiled is not passed!" <<std::endl;
        return 0;
    }
    std::string fileName{argv[1]};
    Lexical_analyzer lex;
    lex.Analyze(fileName);
    lex.PrintTokenList();
    // Parser parser;
    // parser.
   return 0;
}