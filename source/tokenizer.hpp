#pragma once

#include <vector>
#include <string>

namespace regex {
    enum class TokenType {
        kEnd,
        kDigit,
        kWord,
        kStartAnchor,
        kEndAnchor,
        kDot,
        kLeftBrace,
        kRightBrace,
        kDivider,
        kLeftBracket,
        kRightBracket,
        kPlus,
        kQuestion,
        kLiteral
    };

    class Token {
    public:
        Token(TokenType tokenType);
        Token(TokenType tokenType, char payload);
        bool operator==(const Token& other) const;
        TokenType GetTokenType() const;
    private:
        TokenType tokenType_;
        char payload_;
    }

    class Tokenizer {
    public:
        void Tokenizer(const std::string& pattern);

        Token GetNextToken();
        Token Peak(uint32_t n) const;
        void Rewind(uint32_t n);
        bool Match(Token token);
    private: 
        std::vector<Token> tokens;
        size_t currentIdx;
    };
}
