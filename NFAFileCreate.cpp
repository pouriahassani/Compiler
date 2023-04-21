#include "NFAFileCreate.h"
#include "NFA.h"
#include <string>
#include <vector>


RegularExpressionBase::RegularExpressionBase(std::string symbols){
    for(auto i : symbols){
        this->symbols.push_back(i);
    }
};

UniosOperation::UniosOperation(std::string symbols) : RegularExpressionBase(symbols){}
void UniosOperation::CreateRE(RegularExpressionBase* secondRE){

}


ConcatOperation::ConcatOperation(std::string symbols) : RegularExpressionBase(symbols){}

IterationOperation::IterationOperation(std::string symbols) : RegularExpressionBase(symbols){}

PlusOperation::PlusOperation(std::string symbols) : RegularExpressionBase(symbols){}

