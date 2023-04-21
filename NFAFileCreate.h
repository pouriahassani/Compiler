#ifndef NFAFILECREATE_H
#define NFAFILECREATE_H

#include <vector>
#include <string>

class RegularExpressionBase{
    public:
        RegularExpressionBase(std::string symbols);
        virtual void CreateRE(RegularExpressionBase* secondRE) = 0;
    private:
        std::vector<char>symbols;
        std::vector<std::string>lines;
};

class UniosOperation : public RegularExpressionBase{
    public:
        UniosOperation(std::string symbols);
        virtual void CreateRE(RegularExpressionBase* secondRE) override;
    private:
        std::vector<char>symbols;
        std::vector<std::string>lines;
};

class ConcatOperation: public RegularExpressionBase{
    public:
        ConcatOperation(std::string symbols);
        virtual void CreateRE(RegularExpressionBase* secondRE) override;
    private:
        std::vector<char>symbols;
        std::vector<std::string>lines;
};

class IterationOperation : public RegularExpressionBase{
    public:
        IterationOperation(std::string symbols);
        virtual void CreateRE(RegularExpressionBase* secondRE) override;
    private:
        std::vector<char>symbols;
        std::vector<std::string>lines;
};

class PlusOperation : public RegularExpressionBase{
    public:
        PlusOperation(std::string symbols);
        virtual void CreateRE(RegularExpressionBase* secondRE) override;
    private:
        std::vector<char>symbols;
        std::vector<std::string>lines;
};

#endif NFAFILECREATE_H