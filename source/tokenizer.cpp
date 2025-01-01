#include "tokens.hpp"
#include "tokenizer.hpp"

#include <vector>
#include <string>
#include <stdexcept>

namespace regex {
    Tokenizer::Tokenizer(const std::string& pattern) : currentIdx_(0) {
        for (size_t idx = 0; idx < pattern.length(); idx++) {
            if (pattern[idx] ==  '^') {
                tokens_.push_back(Token(TokenType::kStartAnchor));
            } else if (pattern[idx] == '$') {
                tokens_.push_back(Token(TokenType::kEndAnchor));
            } else if (pattern[idx] == '|') {
                tokens_.push_back(Token(TokenType::kDivider));
            } else if (pattern[idx] == '(') {
                tokens_.push_back(Token(TokenType::kLeftBrace));
            } else if (pattern[idx] == ')') {
                tokens_.push_back(Token(TokenType::kRightBrace));
            } else if (pattern[idx] == '[') {
                tokens_.push_back(Token(TokenType::kLeftBracket));
            } else if (pattern[idx] == ']') {
                tokens_.push_back(Token(TokenType::kRightBracket));
            } else if (pattern[idx] == '+') {
                tokens_.push_back(Token(TokenType::kPlus));
            } else if (pattern[idx] == '.') {
                tokens_.push_back(Token(TokenType::kDot));
            } else if (pattern[idx] == '\\' && pattern[idx+1] == 'd') {
                tokens_.push_back(Token(TokenType::kDigit));
            } else if (pattern[idx] == '\\' && pattern[idx+1] == 'w') {
                tokens_.push_back(Token(TokenType::kWord));
            } else {
                tokens_.push_back(Token(TokenType::kLiteral, pattern[idx]));
            }
        }
        tokens_.push_back(Token(TokenType::kEnd));
    }

    Token Tokenizer::GetNextToken() {
        auto token = tokens_[currentIdx_];
        if (token.GetTokenType() != TokenType::kEnd) currentIdx_++;
        return token;
    }

    TokenType Tokenizer::Peak(uint32_t n) const {
        if (currentIdx_ >= tokens_.size()) {
            throw std::runtime_error("Peak");
        }
        return tokens_[currentIdx_].GetTokenType();
    }

    bool Tokenizer::Match(TokenType tokenType) {
        if (tokenType == TokenType::kEnd) throw std::runtime_error("Match");
        if (tokenType == tokens_[currentIdx_].GetTokenType()) {
            currentIdx_++;
            return true;
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& os, const Tokenizer& tokenizer) {
        bool first = false;
        for (const auto& token : tokenizer.tokens_) {
            if (!first) {
                os << " ";
                first = true;
            }
            os << token;
        }
        return os;
    }
}
