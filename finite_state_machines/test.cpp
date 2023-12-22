//#include <iostream>
//#include <fstream>
//#include <map>
//#include <set>
//#include <vector>
//#include <string>
//
//class FiniteStateMachine {
//public:
//    FiniteStateMachine(const std::string& alphabetFile, const std::string& rulesFile, const std::string& terminalStatesFile);
//    bool processInput(const std::string& input);
//
//private:
//    std::set<std::string> alphabet;
//    std::map<std::pair<std::string, std::string>, std::string> transitions;
//    std::set<std::string> finalStates;
//    std::vector<std::string> terminalStates;
//    std::string initialState;
//};
//
//FiniteStateMachine::FiniteStateMachine(const std::string& alphabetFile, const std::string& rulesFile, const std::string& terminalStatesFile) {
//    std::ifstream alphabetStream(alphabetFile);
//    std::string symbol;
//    while (getline(alphabetStream, symbol)) {
//        alphabet.insert(symbol);
//    }
//    alphabetStream.close();
//
//    std::ifstream rulesStream(rulesFile);
//    std::string fromState, toState;
//    std::string inputSymbol;
//    while (rulesStream >> fromState >> inputSymbol >> toState) {
//        if (inputSymbol == "/~") {
//            inputSymbol = " ";
//        }
//        transitions[{fromState, inputSymbol}] = toState;
//        finalStates.insert(toState);
//    }
//    rulesStream.close();
//
//    std::ifstream terminalStatesStream(terminalStatesFile);
//    std::string terminalState;
//    int numTerminalStates;
//    terminalStatesStream >> numTerminalStates;
//    for (int i = 0; i < numTerminalStates; ++i) {
//        terminalStatesStream >> terminalState;
//        terminalStates.push_back(terminalState);
//    }
//    terminalStatesStream.close();
//
//    initialState = "s0";
//}
//
//bool FiniteStateMachine::processInput(const std::string& input) {
//    std::string currentState = initialState;
//    std::string currentSymbol;
//
//    for (char symbol : input) {
//        currentSymbol += symbol;
//
//        // Проверка, что текущий символ принадлежит алфавиту
//        if (alphabet.find(currentSymbol) != alphabet.end()) {
//            // Поиск перехода для текущего состояния и символа
//            auto transition = transitions.find({ currentState, currentSymbol });
//            if (transition == transitions.end()) {
//                std::cout << "Ошибка: невозможен переход из состояния " << currentState
//                    << " по символу '" << currentSymbol << "'." << std::endl;
//                return false;
//            }
//
//            // Обновление текущего состояния
//            currentState = transition->second;
//
//            // Сброс текущего символа
//            currentSymbol.clear();
//        }
//    }
//
//    // Проверка, что текущее состояние является конечным
//    if (finalStates.find(currentState) != finalStates.end()) {
//        // Проверка, что текущее состояние является конечным и принадлежит к числу терминальных состояний
//        if (std::find(terminalStates.begin(), terminalStates.end(), currentState) != terminalStates.end()) {
//            std::cout << "Можно достичь конечного состояния." << std::endl;
//            return true;
//        }
//    }
//
//    std::cout << "Нельзя достичь конечного состояния." << std::endl;
//    return false;
//}
//
//int main() {
//    setlocale(LC_ALL, "RU");
//    std::string alphabetFile = "alphabet.txt";
//    std::string rulesFile = "rules.txt";
//    std::string terminalStatesFile = "terminal_states.txt";
//
//    FiniteStateMachine fsm(alphabetFile, rulesFile, terminalStatesFile);
//
//    std::string input;
//    std::cout << "Введите строку: ";
//    std::getline(std::cin, input);
//
//    fsm.processInput(input);
//
//    return 0;
//}
