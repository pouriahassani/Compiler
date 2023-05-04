#include <iostream>
#include "./Lexical_Analyzer/Lexical_analyzer.h"
#include "./Parser/Parser.h"
#include "./Lexical_Analyzer/NFA.h"
#include <fstream>
#include "./Lexical_Analyzer/NFA_Simulation.h"
#include "./Lexical_Analyzer/RegularExpressionOperations.h"

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
    Parser parser;
    parser.CreateGrammar();
   return 0;
}