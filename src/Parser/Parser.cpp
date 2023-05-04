#include "Parser.h"
#include "Grammar.h"
#include <fstream>
#include <sstream>
#include <string>

Parser::Parser(){};;

void Parser::CreateGrammar(){
    TrimGrammarFile("GrammarDscr");
    std::ifstream grammarFileDscr;
    grammarFileDscr.open("GrammarDscr");
    std::string strLine;
    std::string word;
    std::stringstream ss;
    while(std::getline(grammarFileDscr,strLine)){
        try{
            if(strLine != "Start_grammar")
            throw std::runtime_error{"The format of the input grammar file is not correct"};
        }
        catch(std::runtime_error& runtime_error){
            std::cout << "Error: in line" << strLine << "\n" << runtime_error.what() << std::endl;
            continue;
        }

        std::getline(grammarFileDscr,strLine);
        ss.str(strLine);
        ss >> word;

       try{
            if(word != "Grammar_name:")
            throw std::runtime_error{"The format of the input grammar file is not correct"};
        }
        catch(std::runtime_error& runtime_error){
            std::cout << "Error: in line" << strLine << "\n" << runtime_error.what() << std::endl;
            continue;
        }

        ss >> word;
        Grammar* newGrammar = new Grammar{word};
        std::getline(grammarFileDscr,strLine);
        ss.str(strLine);
        ss >> word;

        try{
            if(word != "Terminals")
            throw std::runtime_error{"The format of the input grammar file is not correct"};
        }
        catch(std::runtime_error& runtime_error){
            std::cout << "Error: in line" << strLine << "\n" << runtime_error.what() << std::endl;
            continue;
        }

        while(ss >> word){
            newGrammar->AddValidTerminal(word);
        }

        std::getline(grammarFileDscr,strLine);
        try{
            if(word != "Productions:")
            throw std::runtime_error{"The format of the input grammar file is not correct"};
        }
        catch(std::runtime_error& runtime_error){
            std::cout << "Error: in line" << strLine << "\n" << runtime_error.what() << std::endl;
            continue;
        }
        while(std::getline(grammarFileDscr,strLine)){
            std::string nonTerminalName;
            ss.str(strLine);
            ss >> nonTerminalName;
            newGrammar->AddNonTerminal(nonTerminalName);
            ss >> word;
            while(ss >> word){
                if(StrToNFA(word) == TerminalType::NON){
                    Symbol newSymbol{word};
                    newGrammar->AddProduction(nonTerminalName,newSymbol);
                }
                    
                else{
                    Symbol newSymbol{StrToNFA(word)};
                    newGrammar->AddProduction(nonTerminalName,newSymbol);
                }
            }
        }
    }
    
    
}