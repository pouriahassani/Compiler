#include <iostream>
#include "Lexical_analyzer.h"
#include "Parser.h"
#include "NFA.h"
#include <fstream>
#include "NFA_Simulation.h"
#include "RegularExpressionOperations.h"
#include <string>
int main(){

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
    for(auto i : symbols){
        std::string s = std::string(1,i);
        NFA symbol{s};
        digits = REO.UnionsOperation(*digits,symbol);
        digits->PrintNFA();
    }
    std::cout << "*******\n\n Digits"<<std::endl;
    std::cout << "*******\n\nUNFADotDigits"<<std::endl;
    dot.PrintNFA();
    UNFADotDigits = REO.ConcatOperation(dot,*digits);
    std::cout << "*******\n\n Digits"<<std::endl;
    std::cout << "*******\n\nOInsDotDigits"<<std::endl;
    OInsDotDigits = REO.oneInstance(*UNFADotDigits);

    std::cout << "*******\n\n InsDotDigits"<<std::endl;
    OInsDotDigits->PrintNFA();
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


// if token name NFA construction
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


// if token name NFA construction
    s = std::string(1,'i');
    NFA iNFA{s};
    s = std::string(1,'f');
    NFA fNFA{s};
    NFA* ifNFA = REO.ConcatOperation(iNFA,fNFA);

/// else token name NFA construction
    s = std::string(1,'e');
    NFA eNFA{s};
    s = std::string(1,'l');
    NFA lNFA{s};
    s = std::string(1,'s');
    NFA sNFA{s};
    NFA* elseNFA = REO.ConcatOperation(*REO.ConcatOperation(*REO.ConcatOperation(eNFA,lNFA),sNFA),eNFA);

/// int token name NFA construction
s = std::string(1,'n');
NFA nNFA{s};
s = std::string(1,'t');
NFA tNFA{s};
NFA* intNFA = REO.ConcatOperation(*REO.ConcatOperation(iNFA,nNFA),tNFA);

/// ws token name NFA construction
s = std::string(1,' ');
NFA blankNFA{s};
s = std::string(1,'\t');
NFA tabNFA{s};
s = std::string(1,'\n');
NFA newlineNFA{s};
NFA* wsNFA = REO.PlusOperation(*REO.UnionsOperation(*REO.UnionsOperation(blankNFA,tabNFA),newlineNFA));

/// ( token name NFA construction
s = std::string(1,'(');
NFA leftPNFA{s};

/// ) token name NFA construction
s = std::string(1,')');
NFA rightPNFA{s};

/// = token name NFA construction
s = std::string(1,'=');
NFA EQNFA{s};

/// ) token name NFA construction
s = std::string(1,'<');
NFA LessNFA{s};

/// > token name NFA construction
s = std::string(1,'>');
NFA rightPNFA{s};
    return 0;
}