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

void Lexical_analyzer::CreateNFAGraphs(){
    // Numbers token name NFA construction
    std::string symbols{"2 3 4 5 6 7 8 9"};
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
    digits = REO.PlusOperation(*REO.UnionsOperation(symbol0,symbol1));
    // std::cout << "*******\n\n Digits"<<std::endl;
    for(auto i : symbols){
        std::string s = std::string(1,i);
        NFA symbol{s};
        digits = REO.UnionsOperation(*digits,symbol);
        // digits->PrintNFA();
    }
    std::cout << "*******\n\n Digits"<<std::endl;
    std::cout << "*******\n\nUNFADotDigits"<<std::endl;
    // dot.PrintNFA();
    UNFADotDigits = REO.ConcatOperation(dot,*digits);
    std::cout << "*******\n\n Digits"<<std::endl;
    std::cout << "*******\n\nOInsDotDigits"<<std::endl;
    OInsDotDigits = REO.oneInstance(*UNFADotDigits);

    std::cout << "*******\n\n InsDotDigits"<<std::endl;
    // OInsDotDigits->PrintNFA();
    std::cout << "*******\n\nDDDC"<<std::endl;
    DDDC = REO.ConcatOperation(*digits,*OInsDotDigits);

    std::cout << "*******\n\nPNNFA"<<std::endl;
    PNNFA = REO.UnionsOperation(PNFA,NNFA);
    std::cout << "*******\n\nPNoneINFA"<<std::endl;
    PNoneINFA = REO.oneInstance(*PNNFA);
    std::cout << "*******\n\nEPNOneINFA"<<std::endl;
    EPNOneINFA = REO.ConcatOperation(ENFA,*PNoneINFA);
    std::cout << "*******\n\nEPNOneIDNFA"<<std::endl;
    EPNOneIDNFA = REO.ConcatOperation(*EPNOneINFA,*digits);
    std::cout << "*******\n\nEPNOneIDOneINFA"<<std::endl;
    EPNOneIDOneINFA = REO.oneInstance(*EPNOneIDNFA);
    std::cout << "*******\n\nnumbers"<<std::endl;
    numbers = REO.ConcatOperation(*DDDC,*EPNOneIDOneINFA);
    std::cout << "*******\n\n*******"<<std::endl;
    numbers->SetNFAType(NFAType::NUMBER);
    NFAGraphs.push_back(numbers);
    

    // id token name NFA construction
    NFA* id;
    NFA* letters;
    NFA* LDU;
    NFA* LDUI;
    std::string letterssymbols{"c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I L K L M N O P Q R S T U V W X Y Z"};
    s = std::string(1,'a');
    NFA symbola{s};
    s = std::string(1,'b');
    NFA symbolb{s};
    letters = REO.UnionsOperation(symbola,symbolb);
    for(auto i : letterssymbols){
        std::string s = std::string(1,i);
        NFA symbol{s};
        letters = REO.UnionsOperation(*letters,symbol);
    }
    LDU = REO.UnionsOperation(*letters,*digits);
    LDUI = REO.IterationOperation(*LDU);
    id = REO.ConcatOperation(*letters,*LDUI);
    id->SetNFAType(NFAType::ID);
    NFAGraphs.push_back(id);
    // id->PrintNFA();
    NFASimulation NFASIM{id};
    std::string str{"i"};
    int lexlesize;
    NFASIM.Simulation(str,lexlesize);
    std::cout << "\nid test: "<<lexlesize <<std::endl;
    // if token name NFA construction
    s = std::string(1,'i');
    NFA iNFA{s};
    s = std::string(1,'f');
    NFA fNFA{s};
    NFA* ifNFA = REO.ConcatOperation(iNFA,fNFA);
    ifNFA->SetNFAPriority(1);
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
    elseNFA->SetNFAPriority(1);
    elseNFA->SetNFAType(NFAType::ELSE);
    NFAGraphs.push_back(elseNFA);

    /// int token name NFA construction
    s = std::string(1,'n');
    NFA nNFA{s};
    s = std::string(1,'t');
    NFA tNFA{s};
    NFA* intNFA = REO.ConcatOperation(*REO.ConcatOperation(iNFA,nNFA),tNFA);
    intNFA->SetNFAPriority(1);
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
    leftPNFA->SetNFAPriority(1);
    leftPNFA->SetNFAType(NFAType::LP);
    NFAGraphs.push_back(leftPNFA);
    leftPNFA->PrintNFA();
    /// ) token name NFA construction
    s = std::string(1,')');
    NFA* rightPNFA = new NFA{s};
    rightPNFA->SetNFAPriority(1);
    rightPNFA->SetNFAType(NFAType::RP);
    NFAGraphs.push_back(rightPNFA);

    /// = token name NFA construction
    s = std::string(1,'=');
    NFA* EQNFA = new NFA{s};
    EQNFA->SetNFAPriority(1);
    EQNFA->SetNFAType(NFAType::EQ);
    NFAGraphs.push_back(EQNFA);

    /// < token name NFA construction
    s = std::string(1,'<');
    NFA* lessNFA = new NFA{s};
    lessNFA->SetNFAPriority(1);
    lessNFA->SetNFAType(NFAType::LT);
    NFAGraphs.push_back(lessNFA);

    /// > token name NFA construction
    s = std::string(1,'>');
    NFA* greatorNFA = new NFA{s};
    greatorNFA->SetNFAPriority(1);
    greatorNFA->SetNFAType(NFAType::GT);
    NFAGraphs.push_back(greatorNFA);
    for(auto i:NFAGraphs){
        i->PrintNFAType();
        for(auto j : i->GetStates()){
            if(j->GetStateType() == StateType::START)
                std::cout << "start state is: " <<j->getStateNumber()<<std::endl;
            if(j->GetStateType() == StateType::ACCEPTING)
                std::cout << "End state is: " <<j->getStateNumber()<<std::endl;
        }
    }
 }

 void Lexical_analyzer::Analyze(std::string fileName){
    fstream fileDcrp;
    fileDcrp.open(fileName);
            std::string s;
    while(std::getline(fileDcrp,s)){
        std::stringstream SS{s};
        // std::cout << s<<std::endl;
        while(SS >> line){
            // std::cout << line<<std::endl;
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
        std::cout << line<<"\nNFA type: ";
        
        NFAPtr->PrintNFAType();
        std::cout <<"longst NFA: "<<LongestNFASize <<"\n\n"<<std::endl;
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
            // if(i.first != NFAType::ID){
                std::pair<NFAType,ReturnTokenAttribute>newToken;
                ReturnTokenAttribute tAttr;
                if(allValidNFAs[0].first != NFAType::ID && allValidNFAs[0].first != NFAType::NUMBER)
                    tAttr.noValue = 1;
            
            newToken = std::make_pair(allValidNFAs[0].first,tAttr);
            TokenList.push_back(newToken);
            // }
        }
    }
    // std::cout << "max lenth is :" << maxLenth<< std::endl;
    line = line.substr(maxLenth,std::string::npos);
    // std::cout << "line is:" << line<< std::endl;
 }


void Lexical_analyzer::GetlongestNFAName(NFASimulation *NFASim, int& LongestNFASize){
    std::string str{*lexemeBeginPtr};
    // int lexemesize;
    NFASim->Simulation(line, LongestNFASize);
        // LongestNFASize++;
    //     lexemeBeginPtr++;
    //     GetlongestNFAName(NFASim,LongestNFASize);
    // }


    // if(NFASim->GetNFAOBject()->GetNFAType() == NFAType::IF)
    //     // NFASim->GetNFAOBject()->PrintNFA();
        // std::cout <<line<< " IF: "<<LongestNFASize<<std::endl;
    // }
        
    return;

}

ReturnTokenAttribute::ReturnTokenAttribute(){};