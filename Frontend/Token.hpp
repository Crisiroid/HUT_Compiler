// Token.hpp

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// Define the TokenType enum for different types of tokens
enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    NUMBER,
    END_OF_FILE,
    UNKNOWN
};

// Define the Token struct to store the type, value, and line number of a token
struct Token {
    TokenType type;
    std::string value;
    int line;

    Token(TokenType type, const std::string& value, int line)
        : type(type), value(value), line(line) {}
};

#endif // TOKEN_H
