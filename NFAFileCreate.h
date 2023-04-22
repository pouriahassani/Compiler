#ifndef NFAFILECREATE_H
#define NFAFILECREATE_H

#include <vector>
#include <string>
#include "NFA.h"

class RegularExpressionOperations{
    public:
        RegularExpressionOperations();
        NFA* UniosOperation(NFA* const leftNFA, NFA* const rightNFA);
        NFA* ConcatOperation(NFA* const leftNFA, NFA* const rightNFA);
        NFA* IterationOperation(NFA* const originalNFA);
        NFA* PlusOperation(NFA* const originalNFA);
    private:
        std::vector<char>symbols;
        std::vector<std::string>lines;
};

#endif