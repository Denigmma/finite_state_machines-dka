#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

class FiniteStateMachine {
public:
    FiniteStateMachine(const std::string& alphabetFile, const std::string& rulesFile, const std::string& terminalStatesFile);
    bool processInput(const std::string& input);

private:
    std::set<std::string> alphabet;
    std::map<std::pair<std::string, std::string>, std::string> transitions;
    std::set<std::string> finalStates;
    std::vector<std::string> terminalStates;
    std::string initialState;
};