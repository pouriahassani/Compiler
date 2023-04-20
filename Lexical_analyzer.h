// This the header file for the lexical analyzer
// In this file there are classes defineing the lecical analyzer's
// functionalities The description of each class is given on top of the class
// decleration

#ifndef LEXYCAL_ANALYZER
#define LEXYCAL_ANALYZER

#include <fstream>
#include <iostream>

class Lexical_analyzer {
public:
  Lexical_analyzer();

private:
  char *forwardPtr;
  char *lexemeBeginPtr;
};

#endif
