#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>

#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine(const std::string& alphabetFile, const std::string& rulesFile, const std::string& terminalStatesFile) {
	std::ifstream alphabetStream(alphabetFile);
	std::string symbol;
	while (getline(alphabetStream, symbol)) {
		alphabet.insert(symbol);
	}
	alphabetStream.close();

	std::ifstream rulesStream(rulesFile);
	std::string fromState, toState;
	std::string inputSymbol;
	while (rulesStream >> fromState >> inputSymbol >> toState) {
		if (inputSymbol == "/~") {
			inputSymbol = " ";
		}
		transitions[{fromState, inputSymbol}] = toState;
		finalStates.insert(toState);
	}
	rulesStream.close();

	std::ifstream terminalStatesStream(terminalStatesFile);
	std::string terminalState;
	int numTerminalStates;
	terminalStatesStream >> numTerminalStates;
	for (int i = 0; i < numTerminalStates; ++i) {
		terminalStatesStream >> terminalState;
		terminalStates.push_back(terminalState);
	}
	terminalStatesStream.close();

	initialState = "s0";
}

bool FiniteStateMachine::processInput(const std::string& input) {
	std::string currentState = initialState;
	std::string currentSymbol;

	for (char symbol : input) {
		currentSymbol += symbol;
		// проверка, что текущий символ принадлежит алфавиту
		if (alphabet.find(currentSymbol) != alphabet.end()) {
			// поиск перехода дл€ текущего состо€ни€ и символа
			auto transition = transitions.find({ currentState, currentSymbol });
			if (transition == transitions.end()) {
				std::cout << "ќшибка: невозможен переход из состо€ни€ " << currentState
					<< " по символу '" << currentSymbol <<"'" << std::endl;
				return false;
			}
			// обновление текущего состо€ни€
			currentState = transition->second;
			// сброс текущего символа
			currentSymbol.clear();
		}
	}

	// проверка, что текущее состо€ние €вл€етс€ конечным
	if (finalStates.find(currentState) != finalStates.end()) {
		// проверка, что текущее состо€ние принадлежит к числу терминальных состо€ний
		if (std::find(terminalStates.begin(), terminalStates.end(), currentState) != terminalStates.end()) {
			std::cout << "ћожно достичь конечного состо€ни€." << std::endl;
			return true;
		}
	}

	std::cout << "Ќельз€ достичь конечного состо€ни€." << std::endl;
	return false;
}

int main() {
	setlocale(LC_ALL, "RU");
	std::string alphabetFile = "alphabet.txt";
	std::string rulesFile = "rules.txt";
	std::string terminalStatesFile = "terminal_states.txt";

	FiniteStateMachine fsm(alphabetFile, rulesFile, terminalStatesFile);

	std::string input;
	std::cout << "¬ведите строку: ";
	std::getline(std::cin, input);

	fsm.processInput(input);

	return 0;
}
