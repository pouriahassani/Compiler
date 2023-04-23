#ifndef RegularExpressionOperations_H
#define RegularExpressionOperations_H

#include <vector>
#include <string>
#include "NFA.h"

class RegularExpressionOperations{
    public:
        RegularExpressionOperations();
        NFA* UnionsOperation(NFA& leftNFA, NFA& rightNFA);
        NFA* ConcatOperation(NFA& leftNFA, NFA& rightNFA);
        NFA* IterationOperation(NFA& originalNFA);
        NFA* PlusOperation(NFA& originalNFA);
    private:
        std::vector<char>symbols;
        std::vector<std::string>lines;
};

#endif