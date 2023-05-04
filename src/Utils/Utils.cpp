#include <string>
#include <bits/stdc++.h>
#include "Utils.h"
#include "Exception.h"


string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}


StateType AssignStateType(int value){
    if(value == -1)
        return StateType::START;
    if(value == 0)
        return StateType::TRANSITION;
    if(value == 1)
        return StateType::ACCEPTING;
    throw StateTypeException{};
}

void TrimGrammarFile(std::string inFileName){
    std::string str;
    std::ifstream in;
    in.open(inFileName);
    if(!in){
    std::cerr << "File "<<inFileName<< " couldn't be opened" << std::endl;
    exit(EXIT_FAILURE);
    }

    std::ofstream out;
    out.open("tmpFile",std::ios::out);
    if(!out){
        std::cerr << "File tmpFile 1 couldn't be opened" << std::endl;
        exit(EXIT_FAILURE);
    }

    while(std::getline(in , str)){
        if(str == "")
            continue;
        str = ltrim(rtrim(str));
        out << str << std::endl;
    }

    in.close();
    out.close();

    in.open("tmpFile");
    if(!in){
        std::cerr << "File tmpfile 2 couldn't be opened" << std::endl;
        exit(EXIT_FAILURE);
    }

    out.open(inFileName,std::ios::out);
    if(!out){
        std::cerr << "File "<<inFileName<< " couldn't be opened" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    while(std::getline(in , str)){
        out << str << std::endl;
    }

    in.close();
    out.close();
}
