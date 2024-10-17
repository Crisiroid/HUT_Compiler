// main.cpp

#include <iostream>
#include <fstream>
#include "Frontend/Scanner.hpp"  // Scanner now handles tokenization

// Function to scan a file line by line using the Scanner
void scanFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filePath << std::endl;
        return;
    }

    Scanner scanner;
    std::string line;
    int lineNumber = 1;

    while (std::getline(file, line)) {
        std::vector<Token> tokens = scanner.scan(line, lineNumber);
        for (const auto& token : tokens) {
            std::cout << "Token: " << token.value << ", Type: "
                      << static_cast<int>(token.type) << ", Line: " << token.line << std::endl;
        }
        lineNumber++;
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    scanFile(filePath);

    return 0;
}
