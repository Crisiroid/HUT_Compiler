#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> // For std::find
#include "Token.hpp"
#include "Keywords.hpp"
#include "Operators.hpp"
#include "Delimiters.hpp"
#include "DFA.hpp"

class Scanner {
public:
    Scanner() : dfa() {}

    // Main scanning function with two arguments
    std::vector<Token> scan(const std::string& line, int& lineNumber) {
        std::vector<Token> tokens;
        std::string tokenValue;
        dfa.reset();

        for (char ch : line) {
            // Check if the character is a delimiter
            if (isDelimiter(std::string(1, ch))) {
                // Process the previous token if there is one
                if (!tokenValue.empty()) {
                    Token token = processToken(tokenValue, lineNumber);
                    tokens.push_back(token);
                    tokenValue = ""; // Reset token value
                }

                // Add the delimiter as its own token
                Token delimiterToken(TokenType::DELIMITER, std::string(1, ch), lineNumber);
                tokens.push_back(delimiterToken);
                dfa.reset(); // Reset DFA for the next token
                continue; // Move to the next character
            }

            // Ignore whitespace
            if (std::isspace(ch)) {
                if (!tokenValue.empty()) {
                    // Process the current token
                    Token token = processToken(tokenValue, lineNumber);
                    tokens.push_back(token);
                    tokenValue = ""; // Reset token value
                }
                dfa.reset();
                continue;
            }

            // Continue building the token
            dfa.transition(ch);
            tokenValue += ch;

            // Process token if DFA reaches a final state
            if (dfa.getCurrentState() == State::DONE) {
                Token token = processToken(tokenValue, lineNumber);
                tokens.push_back(token);
                tokenValue = ""; // Reset token value
                dfa.reset(); // Reset DFA for the next token
            }
        }

        // Handle any remaining token at the end of the line
        if (!tokenValue.empty()) {
            Token token = processToken(tokenValue, lineNumber);
            tokens.push_back(token);
        }

        return tokens;
    }

private:
    DFA dfa;

    Token processToken(const std::string& value, int line) {
        TokenType type = identifyTokenType(value);
        return Token(type, value, line);
    }

    TokenType identifyTokenType(const std::string& value) {
        // Check the state of the DFA to identify the token type
        if (dfa.getCurrentState() == State::IN_KEYWORD) {
            if (isKeyword(value)) {
                return TokenType::KEYWORD;
            }
        }

        if (dfa.getCurrentState() == State::IN_NUMBER) {
            return TokenType::NUMBER;
        } else if (dfa.getCurrentState() == State::IN_OPERATOR) {
            return TokenType::OPERATOR;
        } else if (isDelimiter(value)) {
            return TokenType::DELIMITER;
        }

        return TokenType::IDENTIFIER; // Default to identifier
    }

    static bool isKeyword(const std::string& value) {
        return std::find(Keywords::getKeywords().begin(), Keywords::getKeywords().end(), value) != Keywords::getKeywords().end();
    }

    static bool isDelimiter(const std::string& value) {
        return std::find(Delimiters::getDelimiters().begin(), Delimiters::getDelimiters().end(), value) != Delimiters::getDelimiters().end();
    }
};

#endif // SCANNER_HPP
