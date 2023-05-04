#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <bits/stdc++.h>
#include "Exception.h"

using namespace std;
string ltrim(const string &str);

string rtrim(const string &str);

enum class StateType{
    START=-1,
    TRANSITION,
    ACCEPTING
};

StateType AssignStateType(int value);

// This function is for removing the newline and prefix and postfix space of the line the 
// inFileName file and rewrites the content of the inFileName 
void TrimGrammarFile(std::string inFileName);



#endif