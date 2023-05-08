#include "Parser.h"
#include "Grammar.h"
#include <fstream>
#include <sstream>
#include <string>

Parser::Parser(){};

/* Creates the grammar using the the ifstream GrammarFileDscr
 first the name of the grammar is written in the file and then the
 terminal and non terminals are listed with each list in one line
 later the production for each non terminal is listed line by line.
 end of grammar is detected by line written as "End Grammar"
 This is done for all the grammar defined in the file and for each grammar
 the pointer to class Grammar is pushed to the GrammarVec of the parser*/
 /*

 After creating the productions, for each terminal symbol, the 
 first and follow is calculated using FindFirst and FindFollow functions.
 for the first function since the calculation is done recurrsively,
 we only call FindFirst for the start symbol
 */
void Parser::CreateGrammar(){
    char* homeDir = getenv("HOME_DIR");
    if(homeDir == NULL){
        std::cerr << *homeDir<<"couldn't get the home directory"<<std::endl;
        exit(EXIT_FAILURE);
    }
    std::string GrammarDscr{homeDir};
    GrammarDscr+="/src/Parser/GrammarDscr";
    TrimGrammarFile(GrammarDscr);
    std::ifstream grammarFileDscr;
    grammarFileDscr.open(GrammarDscr);
    std::string strLine;
    std::string word;
    std::stringstream ss;
    while(std::getline(grammarFileDscr,strLine)){
        try{
            if(strLine != "Start_grammar")
            throw std::runtime_error{"The format of the input grammar in Start_grammar line is not correct"};
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
            throw std::runtime_error{"The format of the input grammar in line Grammar_name is not correct"};
        }
        catch(std::runtime_error& runtime_error){
            std::cout << "Error: in line" << strLine << "\n" << runtime_error.what() << std::endl;
            continue;
        }

        ss >> word;
        Grammar* newGrammar = new Grammar{word};
        std::getline(grammarFileDscr,strLine);
        ss.clear();
        ss.str(strLine);
        ss >> word;
        
        try{
            if(word != "Terminals:")
            throw std::runtime_error{"The format of the input grammar in line Terminals is not correct"};
        }
        catch(std::runtime_error& runtime_error){
            std::cout << "Error: in line " << strLine <<" \n " << runtime_error.what() << std::endl;
            continue;
        }

        while(ss >> word){
            newGrammar->AddTerminal(word);
        }
        std::getline(grammarFileDscr,strLine);
        ss.clear();
        ss.str(strLine);
        ss >> word;
        
        try{
            if(word != "NonTerminals:")
            throw std::runtime_error{"The format of the input grammar in line NonTerminals is not correct"};
        }
        catch(std::runtime_error& runtime_error){
            std::cout << "Error: in line " << strLine <<" \n " << runtime_error.what() << std::endl;
            continue;
        }
        ss >> word;
        newGrammar->AddNonTerminal(word);
        newGrammar->SetStartSymbol(word);
        while(ss >> word){
            newGrammar->AddNonTerminal(word);
        }
        ss.clear();
        std::getline(grammarFileDscr,strLine);
        ss.str(strLine);
        ss >> word;
        try{
            if(word != "Productions:")
            throw std::runtime_error{"The format of the input grammar line Productions is not correct"};
        }
        catch(std::runtime_error& runtime_error){
            std::cout << "Error: in line" << strLine <<" "<<word<<" \n" << runtime_error.what() << std::endl;
            continue;
        }
        
        while(std::getline(grammarFileDscr,strLine)){
            if(strLine == "End_Grammar")
                break;
            std::string nonTerminalName;
            ss.clear();
            ss.str(strLine);
            ss >> nonTerminalName;
            Symbol* newNonTerminal;
            if(newGrammar->GetNonTerminal().find(nonTerminalName) != newGrammar->GetNonTerminal().end())
                newNonTerminal = newGrammar->GetNonTerminal().at(nonTerminalName);
            
            else{
                std::cout << "Couldnt find the non terminal in the list of the non terminals to add production " <<std::endl;
                exit(EXIT_FAILURE);
            }             
            
            ss >> word;
            std::vector<Symbol*>newProducion;
            while(ss >> word){
                if(word == "|"){
                    newGrammar->AddProduction(newNonTerminal,newProducion);
                    newProducion.clear();
                }
                else{
                    if(word == "eps"){
                        newProducion.push_back(newGrammar->GetEps());
                        continue;
                    }
                    if(StrToNFA(word) == TerminalType::NON){
                        try{
                            if(newGrammar->GetNonTerminal().find(word) != newGrammar->GetNonTerminal().end()){
                                newProducion.push_back(newGrammar->GetNonTerminal().find(word)->second);
                            }
                            else{
                                std::cout <<"Couldnt find the non terminal " << word << " in the list of the non terminals to add production"<<std::endl;
                                exit(EXIT_FAILURE);
                            }
                        }
                        catch(const std::exception& e) {
                            std::cerr << "Error adding symbol in the new production: "<< strLine << e.what() << std::endl;
                        }
                    }
                        
                    else{
                        try{
                            if(newGrammar->GetTerminals().find(word) != newGrammar->GetTerminals().end()){
                                newProducion.push_back(newGrammar->GetTerminals().find(word)->second);
                            }
                            else{
                                std::cout << "Couldnt find the terminal " << word << " in the list of the non terminals to add production"<<std::endl;
                                exit(EXIT_FAILURE);
                            }
                        }
                        catch(const std::exception& e) {
                            std::cerr << "Error adding symbol in the new production: "<< strLine << e.what() << std::endl;
                        }
                    }
                }
            }
            newGrammar->AddProduction(newNonTerminal,newProducion);
            newProducion.clear();
        }
        ss.clear();
        std::cout << newGrammar->GetStartSymbol() <<std::endl;
        for(auto i:newGrammar->GetNonTerminal()){
            std::cout << i.first;
            i.second->PrintSymbol();
            std::cout << std::endl;
            newGrammar->FindFirst(i.second);
        }
        // Find first of the start symbol. This will calculate the start symbol of the rest of
        // Symbols in the non terminals
        newGrammar->FindFirst(newGrammar->GetNonTerminal().at(newGrammar->GetStartSymbol()));
        
        // Find the follow of all of the non terminals
        for(auto i:newGrammar->GetNonTerminal()){
            std::cout<<"original symbol ";
            i.second->PrintSymbol() ;
            std::cout<<"--> ";
            newGrammar->FindFollow(i.second);
            std::cout<<"\n";
        }

        newGrammar->PrintGrammar();
        grammarvec.push_back(newGrammar);
    }   
}