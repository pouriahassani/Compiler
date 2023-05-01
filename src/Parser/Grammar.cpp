#include "Grammar.h"
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

// Basic constructor to just set the name of the grammar
Grammar::Grammar(std::string grammarName)
: grammarName(grammarName){};

/* Creates the grammar using the the ifstream GrammarFileDscr
 first the name of the grammar is written in the file and then the 
 terminal and non terminals are listed with each list in one line
 later the production for each non terminal is listed line by line.
 end of grammar is detected by line written as "End Grammar"*/
void Grammar::CreateGrammar(std::ifstream GrammarFileDscr){
  std::string strline{""};

  while (strline != "End Grammar"){
    std::getline(GrammarFileDscr,strline);
    if(strline == "")
        continue;
    std::stringstream line{strline};
    std::string 


  }
}