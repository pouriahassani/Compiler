// This is the implementation of Pareser's classes
// Parser will call Lexical_analizer's classes to get the next token for grammatical error check
#ifndef PARSER
#define PARSER

#include <iostream>
#include <fstream>
#include "Lexical_analyzer.h"

class Parser{
    public:
        Parser();
        void getNextToken();
    private:
        Lexical_analyzer lexical_analyzer;       

};


#endif

