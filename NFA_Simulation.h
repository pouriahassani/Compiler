#ifndef NFA_SIMULATION_H
#define NFA_SIMULATION_H

#include "NFA.h"
#include <stack>
#include <vector>
#include <iostream>
#include <string>
#include <set>
class NFASimulation{
    public:
    NFASimulation(NFA* NFAObject);
    bool Simulation(std::string line);
    std::set<int>& Move(std::set<int>& S, char c); 
    std::set<int>& Eclosure(std::set<int>& S); 


    private:
    NFA* NFAObject;
    std::stack<int> oldStack;
    std::stack<int> newStack;
    std::vector<bool> alreadyOn;
    void addState(int stateNumber);
};

#endif