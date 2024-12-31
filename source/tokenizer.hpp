#pragma once

#include "tokens.hpp"

#include <vector>
#include <string>

namespace regex {
    class Tokenizer {
    public:
        Tokenizer(const std::string& pattern);
        void Rewind(uint32_t n);
        [[nodiscard]] Token GetNextToken();
        [[nodiscard]] bool Match(TokenType token);
        [[nodiscard]] TokenType Peak(uint32_t n = 0) const;
        friend std::ostream& operator<<(std::ostream& os, const Tokenizer& token);
    private: 
        std::vector<Token> tokens_;
        size_t currentIdx_;
    };
}
