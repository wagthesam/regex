#include "tokens.hpp"

namespace regex {
    const std::unordered_map<TokenType, std::string> tokenTypeToString = {  
        {TokenType::kEnd, "EOF"},  
        {TokenType::kDigit, "\\d"},  
        {TokenType::kWord, "\\w"},  
        {TokenType::kStartAnchor, "^"},  
        {TokenType::kEndAnchor, "$"},  
        {TokenType::kDot, "."},  
        {TokenType::kLeftBrace, "("},  
        {TokenType::kRightBrace, ")"},  
        {TokenType::kDivider, "|"},  
        {TokenType::kLeftBracket, "["},  
        {TokenType::kRightBracket, "]"},  
        {TokenType::kPlus, "+"},  
        {TokenType::kQuestion, "?"},  
    };

    bool Token::operator==(const Token& other) const {
        return tokenType_ == other.tokenType_ && payload_ == other.payload_;
    }

    TokenType Token::GetTokenType() const {
        return tokenType_;
    }

    char Token::GetPayload() const {
        return payload_;
    }

    Token::Token(TokenType tokenType, char payload) : tokenType_(tokenType), payload_(payload) {}

    Token::Token(TokenType tokenType) : tokenType_(tokenType), payload_('\0') {}

    std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << tokenTypeToString.at(token.GetTokenType());
        return os;
    }
}