#ifndef DFA_HPP
#define DFA_HPP

#include "Operators.hpp"
#include <cctype>

enum class State {
    START,      // Initial state
    IN_KEYWORD, // Processing a potential keyword
    IN_NUMBER,  // Processing a number
    IN_OPERATOR,// Processing an operator
    IN_IDENTIFIER, // Processing an identifier
    DONE        // Final state
};

class DFA {
public:
    DFA() : currentState(State::START) {}

    [[nodiscard]] State getCurrentState() const {
        return currentState;
    }

    // Transitions the DFA based on the input character
    void transition(char ch) {
        switch (currentState) {
            case State::START:
                if (std::isalpha(ch)) {
                    currentState = State::IN_KEYWORD;
                } else if (std::isdigit(ch)) {
                    currentState = State::IN_NUMBER;
                } else if (isOperatorChar(ch)) {
                    currentState = State::IN_OPERATOR;
                } else {
                    currentState = State::START;
                }
                break;

            case State::IN_KEYWORD:
                if (std::isalnum(ch)) {
                    currentState = State::IN_KEYWORD;
                } else {
                    currentState = State::DONE;
                }
                break;

            case State::IN_NUMBER:
                if (std::isdigit(ch)) {
                    currentState = State::IN_NUMBER;
                } else {
                    currentState = State::DONE;
                }
                break;

            case State::IN_OPERATOR:
                currentState = State::DONE;
                break;

            default:
                currentState = State::START;
                break;
        }
    }

    // Resets the DFA to the START state
    void reset() {
        currentState = State::START;
    }

    // Helper function to identify operator characters
    static bool isOperatorChar(char ch) {
        // Check if the character matches any of the operator strings
        for (const auto& op : Operators::getOperators()) {
            if (op.length() == 1 && op[0] == ch) {
                return true; // Single-character operator match
            }
        }
        return false; // Not a matching operator
    }

private:
    State currentState;
};

#endif // DFA_HPP
