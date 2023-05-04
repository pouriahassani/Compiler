// This is the implementation of Pareser's classes
// Parser will call Lexical_analizer's classes to get the next token for grammatical error check
#ifndef PARSER
#define PARSER

#include <iostream>
#include <fstream>
#include "./../Lexical_Analyzer/Lexical_analyzer.h"
#include "Grammar.h"

class Parser{
    public:
        Parser();
        void GetNextToken();
        void CreateGrammar();
    private:
        Lexical_analyzer lexical_analyzer;   
        std::vector<Grammar*>grammarvec;    

};

#endif

