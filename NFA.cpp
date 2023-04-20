
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include "NFA.h"
#include "Exception.h"
#include "Utils.h"

State::State(int stateNumber) { this->stateNumber = stateNumber; }

void State::AddEpsEdge(int nextStateNumber) {
  epsClosureStates.push_back(nextStateNumber);
}

void State::AddEdge(std::string edge, int nextStateNumber) {
  nonEpsClosureNextStates[nextStateNumber] = edge;
}

const int State::getStateNumber(){
    return stateNumber;
}


const std::unordered_map<int, std::string>& State::GetnonEpsClosureNextStates(){
    return nonEpsClosureNextStates;
}

const std::vector<int>& State::GetepsClosureStates(){
    return epsClosureStates;
}

NFA::NFA(int numberOfStates) : numberOfStates(numberOfStates) {
  for(int i{0};i<numberOfStates;i++){
    State* newState = new State(i);
    States.push_back(newState);
  }
}

const void NFA::PrintNFA(){
    for(auto i:States){
        std::cout << i->getStateNumber() << ": " <<std::endl;
        std::cout <<"epsilon edges:"<<std::endl;
        for(auto j : i->GetepsClosureStates()){
            std::cout << j<<", ";
        }
        std::cout << "\n"<<"non epsilon edges:"<<std::endl;
        for(auto j : i->GetnonEpsClosureNextStates()){
            std::cout << j.first << ':' << j.second<<", ";
        }
        std::cout << std::endl;
    }
}

const std::vector<State *>& NFA::GetStates(){
    return States;
}

void NFA::CreateNFA(std::ifstream& edgesStatesFile){
    std::string edge;
    std::string currStateNumber;
    std::string nextStateNumber;
    std::string isEps;
    std::string S;
    while(std::getline(edgesStatesFile,S)){
            S = ltrim(rtrim(S));
            std::cout << S <<std::endl;
            if(S == "")
                continue;

            std::stringstream line(S);
            line >> isEps;
            line >> currStateNumber;
            line >> nextStateNumber;

            if(stoi(isEps) == 0){
                if(!(line >> edge))
                    throw FileReadException{};
            }

            if(stoi(isEps) == 0)
                States[stoi(currStateNumber)]->AddEdge(edge,stoi(nextStateNumber));
            else
                States[stoi(currStateNumber)]->AddEpsEdge(stoi(nextStateNumber));
    }   
    PrintNFA();
}


