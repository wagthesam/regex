#include "tokenizer.hpp"
#include "parser.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    std::string inputText;
    std::string pattern;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--input_text") == 0 && i + 1 < argc) {
            inputText = argv[++i];
        } else if (std::strcmp(argv[i], "--pattern") == 0 && i + 1 < argc) {
            pattern = argv[++i];
        }
    }

    regex::Tokenizer tokenizer(pattern);

    std::cout << "Tokens: " << tokenizer << std::endl;

    return 0;
}