#include <iostream>
#include <fstream> // To read the file line by line
#include "Frontend/Scanner.hpp"

void scanFile(const std::string& filename) {
    Scanner scanner;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 1;
    while (std::getline(file, line)) {
        std::vector<Token> tokens = scanner.scan(line, lineNumber); // Pass each line and the line number
        for (const Token& token : tokens) {
            std::cout << "Token: " << token.value << ", Type: " << token.getTypeAsString() << ", Line: " << token.line << std::endl;
        }
        lineNumber++;
    }

    file.close();
}

int main() {
    std::string filename = "test.hol";
    scanFile(filename);
    return 0;
}
