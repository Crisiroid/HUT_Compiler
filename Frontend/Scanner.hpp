// Scanner.hpp

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "Token.hpp"
#include "Keywords.hpp"
#include "Operators.hpp"
#include "Delimiters.hpp"

// Scanner class to scan and tokenize the input
class Scanner {
private:
    std::vector<std::string> keywords = {"int", "float", "if", "else", "for", "while", "return"};
    std::vector<std::string> operators = {"+", "-", "*", "/", "=", "=="};

public:
    bool isKeyword(const std::string& word) {
        return std::find(Keywords::getKeywords().begin(), Keywords::getKeywords().end(), word) != Keywords::getKeywords().end();
    }

    bool isOperator(const std::string& word) {
        return std::find(Operators::getOperators().begin(), Operators::getOperators().end(), word) != Operators::getOperators().end();
    }

    bool isDelimiter(const std::string& word) {
        return std::find(Delimiters::getDelimiters().begin(), Delimiters::getDelimiters().end(), word) != Delimiters::getDelimiters().end();
    }
    // Method to scan a line of code and return a list of tokens
    std::vector<Token> scan(const std::string& code, int line) {
        std::vector<Token> tokens;
        size_t i = 0;
        while (i < code.length()) {
            // Skip whitespace
            if (std::isspace(code[i])) {
                ++i;
                continue;
            }

            // Check for keywords and identifiers
            if (std::isalpha(code[i])) {
                size_t start = i;
                while (i < code.length() && (std::isalnum(code[i]) || code[i] == '_')) {
                    ++i;
                }
                std::string word = code.substr(start, i - start);

                if (isKeyword(word)) {
                    tokens.emplace_back(TokenType::KEYWORD, word, line);
                } else {
                    tokens.emplace_back(TokenType::IDENTIFIER, word, line);
                }
            }
            // Check for numbers
            else if (std::isdigit(code[i])) {
                size_t start = i;
                while (i < code.length() && std::isdigit(code[i])) {
                    ++i;
                }
                std::string number = code.substr(start, i - start);
                tokens.emplace_back(TokenType::NUMBER, number, line);
            }
            // Check for operators
            else if (isOperator(std::string(1, code[i]))) {
                size_t start = i;
                ++i;
                if (i < code.length() && isOperator(code.substr(start, 2))) {
                    tokens.emplace_back(TokenType::OPERATOR, code.substr(start, 2), line);
                    ++i;
                } else {
                    tokens.emplace_back(TokenType::OPERATOR, code.substr(start, 1), line);
                }
            }
            // Unknown characters
            else {
                tokens.emplace_back(TokenType::UNKNOWN, std::string(1, code[i]), line);
                ++i;
            }
        }
        return tokens;
    }
};

#endif // SCANNER_H
