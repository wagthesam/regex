#pragma once

#include "tokenizer.hpp"

#include <vector>
#include <string>
#include <stdexcept>

namespace regex {
    bool Token::operator==(const Token& other) const {
        return tokenType_ == other.tokenType_ && payload_ == other.payload_;
    }

    TokenType Token::GetTokenType() const {
        return tokenType_;
    }

    Token::Token(TokenType tokenType, char payload) : tokenType_(tokenType), payload_(payload) {}

    Token::Token(TokenType tokenType) : tokenType_(tokenType), payload_('\0') {}

    void Tokenizer::Tokenizer(const std::string& pattern) : currentIdx(0) {
        for (size_t idx = 0; idx < pattern.length(), idx++) {
            if (pattern[idx] ==  '^') {
                tokens.push_back(Token::kStartAnchor);
            } else if (pattern[idx] == '$') {
                tokens.push_back(Token::kEndAnchor);
            } else if (pattern[idx] == '|') {
                tokens.push_back(Token::kDivider);
            } else if (pattern[idx] == '(') {
                tokens.push_back(Token::kLeftBrace);
            } else if (pattern[idx] == ')') {
                tokens.push_back(Token::kRightBrace);
            } else if (pattern[idx] == '[') {
                tokens.push_back(Token::kLeftBracket);
            } else if (pattern[idx] == ']') {
                tokens.push_back(Token::kRightBracket);
            } else if (pattern[idx] == '+') {
                tokens.push_back(Token::kPlus);
            } else if (pattern[idx] == '.') {
                tokens.push_back(Token::kDot);
            } else if (pattern[idx] == '\\' && pattern[idx+1] == 'd') {
                tokens.push_back(Token::kDigit);
            } else if (pattern[idx] == '\\' && pattern[idx+1] == 'w') {
                tokens.push_back(Token::kWord);
            } else {
                tokens.push_back(Token::kLiteral, pattern[idx]);
            }
        }
        tokens.push_back(Token::kEnd);
    }

    Token Tokenizer::GetNextToken() {
        auto token = tokens[currentIdx];
        if (token.GetType() != TokenType.kEnd) currentIdx++;
        return token;
    }

    Token Tokenizer::Peak(uint32_t n) const {
        if (currentIdx >= tokens.length()) {
            throw std::runtime_error("Peak");
        }
        return tokens[currentIdx];
    }

    Token Tokenizer::Rewind(uint32_t n) {
        auto rewindIdx = static_cast<int32_t>(currentIdx) - static_cast<int32_t>(n);
        if (rewindIdx < 0) {
            throw std::runtime_error("Rewind");
        }
        return tokens[rewindIdx];
    }

    bool Tokenizer::Match(Token token) const {
        if (token.GetType() == TokenType::kEnd) throw std::runtime_error("Match");
        if (token == tokens[currentIdx]) {
            currentIdx++;
            return true;
        }
        return false;
    }
}
