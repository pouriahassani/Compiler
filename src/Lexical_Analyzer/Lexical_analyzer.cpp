#include "Lexical_analyzer.h"
#include "RegularExpressionOperations.h"
#include <string>
#include "NFA.h"
#include <iostream>
#include <sstream>
#include "NFA_Simulation.h"
// Lexical_analyzer class constructor
Lexical_analyzer::Lexical_analyzer(){
    CreateNFAGraphs();
};

void Lexical_analyzer::PrintTokenList()const{
    for(const auto &i:TokenList){
        NFAType typeOfNFA = i.first;
        if (typeOfNFA == NFAType::ID){
            std::cout << "ID: " << i.second.IDvalue <<std::endl;
        }
        if (typeOfNFA == NFAType::NUMBER)
            std::cout << "NUMBER: " << i.second.IDvalue<<std::endl;
        if (typeOfNFA == NFAType::ELSE)
            std::cout << "ELSE" << std::endl;
        if (typeOfNFA == NFAType::EQ)
            std::cout << "EQ" << std::endl;
        if (typeOfNFA == NFAType::GT)
            std::cout << "GT" << std::endl;
        if (typeOfNFA == NFAType::IF)
            std::cout << "IF" << std::endl;
        if (typeOfNFA == NFAType::INT)
            std::cout << "INT" << std::endl;
        if (typeOfNFA == NFAType::LP)
            std::cout << "LP" << std::endl;
        if (typeOfNFA == NFAType::LT)
            std::cout << "LT" << std::endl;
        if (typeOfNFA == NFAType::RP)
            std::cout << "RP" << std::endl;
        if (typeOfNFA == NFAType::SC)
            std::cout << "SC" << std::endl;
        if (typeOfNFA == NFAType::WS)
            std::cout << "WS" << std::endl;
    }
}


void Lexical_analyzer::CreateNFAGraphs(){
    // Numbers token name NFA construction
    std::string symbols{"0 1 2 3 4 5 6 7 8 9"};
    NFA* digit;
    NFA* digits;
    std::string symbolsDot = ".";
    std::string symbolsE = "E";
    std::string symbolsP = "+";
    std::string symbolsN = "-";
    NFA dot{symbolsDot};
    NFA ENFA{symbolsE};
    NFA PNFA{symbolsP};
    NFA NNFA{symbolsN};
    NFA* UNFADotDigits;
    NFA* OInsDotDigits;
    NFA* PNoneINFA;
    NFA* EPNNFA;
    NFA* EPNOneINFA;
    NFA *EPNOneIDNFA;
    NFA *EPNOneIDOneINFA;
    NFA *DDDC;
    NFA* PNNFA;
    NFA* numbers;
    RegularExpressionOperations REO{};
    std::string s = std::string(1,'0');
    NFA symbol0{s};
    s = std::string(1,'1');
    NFA symbol1{s};
    digit = new NFA(symbols,0);
    digits = REO.PlusOperation(*digit);
    UNFADotDigits = REO.ConcatOperation(dot,*digits);
    OInsDotDigits = REO.oneInstance(*UNFADotDigits);
    DDDC = REO.ConcatOperation(*digits,*OInsDotDigits);
    PNNFA = REO.UnionsOperation(PNFA,NNFA);
    PNoneINFA = REO.oneInstance(*PNNFA);
    EPNOneINFA = REO.ConcatOperation(ENFA,*PNoneINFA);
    EPNOneIDNFA = REO.ConcatOperation(*EPNOneINFA,*digits);
    EPNOneIDOneINFA = REO.oneInstance(*EPNOneIDNFA);
    numbers = REO.ConcatOperation(*DDDC,*EPNOneIDOneINFA);
    numbers->SetNFAType(NFAType::NUMBER);
    NFAGraphs.push_back(numbers);
    

    // id token name NFA construction
    NFA* id;
    NFA* letter;
    NFA* letters;
    NFA* LDU;
    NFA* LDUI;
    std::string letterssymbols{"a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I L K L M N O P Q R S T U V W X Y Z"};
    letter = new NFA(letterssymbols,0);
    LDU = REO.UnionsOperation(*letter,*digit);
    LDUI = REO.IterationOperation(*LDU);
    id = REO.ConcatOperation(*letter,*LDUI);
    id->SetNFAType(NFAType::ID);
    NFAGraphs.push_back(id);

    // if token name NFA construction
    s = std::string(1,'i');
    NFA iNFA{s};
    s = std::string(1,'f');
    NFA fNFA{s};
    NFA* ifNFA = REO.ConcatOperation(iNFA,fNFA);
    ifNFA->SetNFAType(NFAType::IF);
    NFAGraphs.push_back(ifNFA);

    /// else token name NFA construction
    s = std::string(1,'e');
    NFA eNFA{s};
    s = std::string(1,'l');
    NFA lNFA{s};
    s = std::string(1,'s');
    NFA sNFA{s};
    NFA* elseNFA = REO.ConcatOperation(*REO.ConcatOperation(*REO.ConcatOperation(eNFA,lNFA),sNFA),eNFA);
    
    elseNFA->SetNFAType(NFAType::ELSE);
    NFAGraphs.push_back(elseNFA);

    /// int token name NFA construction
    s = std::string(1,'n');
    NFA nNFA{s};
    s = std::string(1,'t');
    NFA tNFA{s};
    NFA* intNFA = REO.ConcatOperation(*REO.ConcatOperation(iNFA,nNFA),tNFA);
    
    intNFA->SetNFAType(NFAType::INT);
    NFAGraphs.push_back(intNFA);

    /// ws token name NFA construction
    s = std::string(1,' ');
    NFA blankNFA{s};
    s = std::string(1,'\t');
    NFA tabNFA{s};
    s = std::string(1,'\n');
    NFA newlineNFA{s};
    NFA* wsNFA = REO.PlusOperation(*REO.UnionsOperation(*REO.UnionsOperation(blankNFA,tabNFA),newlineNFA));
    wsNFA->SetNFAType(NFAType::WS);
    NFAGraphs.push_back(wsNFA);

    /// ( token name NFA construction
    s = std::string(1,'(');
    NFA* leftPNFA = new NFA{s};
    
    leftPNFA->SetNFAType(NFAType::LP);
    NFAGraphs.push_back(leftPNFA);

    /// ) token name NFA construction
    s = std::string(1,')');
    NFA* rightPNFA = new NFA{s};
    
    rightPNFA->SetNFAType(NFAType::RP);
    NFAGraphs.push_back(rightPNFA);

    /// = token name NFA construction
    s = std::string(1,'=');
    NFA* EQNFA = new NFA{s};
    
    EQNFA->SetNFAType(NFAType::EQ);
    NFAGraphs.push_back(EQNFA);

    /// < token name NFA construction
    s = std::string(1,'<');
    NFA* lessNFA = new NFA{s};
    
    lessNFA->SetNFAType(NFAType::LT);
    NFAGraphs.push_back(lessNFA);

    /// > token name NFA construction
    s = std::string(1,'>');
    NFA* greatorNFA = new NFA{s};
    
    greatorNFA->SetNFAType(NFAType::GT);
    NFAGraphs.push_back(greatorNFA);
 }

 void Lexical_analyzer::Analyze(std::string fileName){
    std::ifstream fileDcrp(fileName);
    try{
        if(!fileDcrp)
            throw std::runtime_error("Falied to open the source prgram file");
    }
    catch(const std::exception* E){
        std::cerr << "Error: "<<E->what()<<std::endl;
    return;
    }

            std::string s;
    while(std::getline(fileDcrp,s)){
        std::stringstream SS{s};
        while(SS >> line){
            try{
                while(line != "")
                    ExtractTokens();
            }
            catch( const InvalidSyntax& InvalidSyntax){
                std::cout << InvalidSyntax.what()<<std::endl;
            }
        }
    }
 }

 void Lexical_analyzer::ExtractTokens(){
    std::vector<std::pair<NFAType,int>>allValidNFAs;
    int counter{0};


    for(auto NFAPtr: NFAGraphs){
        counter+=1;
        lexemeBeginPtr = &line[0];
        int LongestNFASize = 0;
        NFASimulation* NFASim = new NFASimulation{NFAPtr};
        GetlongestNFAName(NFASim, LongestNFASize);

    
        if(LongestNFASize > 0){
            allValidNFAs.push_back({NFAPtr->GetNFAType(),LongestNFASize});
        }
    }
    if(allValidNFAs.size() == 0)
        throw InvalidSyntax{};

    std::vector<std::pair<NFAType,int>>longestTokens;
    int maxLenth = 0;
    for(auto i : allValidNFAs){
        if(i.second > maxLenth)
            maxLenth = i.second; 
    }

    for(auto i : allValidNFAs){
        if(i.second == maxLenth)
            longestTokens.push_back(i); 
    }

    if(longestTokens.size() == 1){
        std::pair<NFAType,ReturnTokenAttribute>newToken;
        ReturnTokenAttribute tAttr;
        if(allValidNFAs[0].first == NFAType::ID || allValidNFAs[0].first == NFAType::NUMBER)
            tAttr.IDvalue = line.substr(0,allValidNFAs[0].second);
        else
            tAttr.noValue = 1;
            
            newToken = std::make_pair(allValidNFAs[0].first,tAttr);
            TokenList.push_back(newToken);
    }

    else{
        for(auto i : longestTokens){
            std::pair<NFAType,ReturnTokenAttribute>newToken;
            ReturnTokenAttribute tAttr;
            tAttr.noValue = 1;
            if(i.first == NFAType::ID)
                continue;
            newToken = std::make_pair(i.first,tAttr);
            TokenList.push_back(newToken);
        }
    }
    line = line.substr(maxLenth,std::string::npos);
 }


void Lexical_analyzer::GetlongestNFAName(NFASimulation *NFASim, int& LongestNFASize){
    std::string str{*lexemeBeginPtr};
    NFASim->Simulation(line, LongestNFASize);  
    return;

}

ReturnTokenAttribute::ReturnTokenAttribute(){};