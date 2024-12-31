#pragma once

#include <unordered_map>
#include <ostream>

namespace regex {
    enum class TokenType {
        kEnd,//
        kDigit,//
        kWord,//
        kStartAnchor,//
        kEndAnchor,//
        kDot, //
        kLeftBrace,
        kRightBrace,
        kDivider,
        kLeftBracket,
        kRightBracket,
        kPlus, //
        kQuestion, //
        kLiteral
    };

    class Token {
    public:
        Token(TokenType tokenType);
        Token(TokenType tokenType, char payload);
        [[nodiscard]] TokenType GetTokenType() const;
        [[nodiscard]] char GetPayload() const;
        bool operator==(const Token& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Token& token);
    private:
        TokenType tokenType_;
        char payload_;
    };
}