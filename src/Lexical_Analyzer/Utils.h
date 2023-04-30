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



#endif