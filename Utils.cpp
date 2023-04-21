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

