#include "parser.hpp"
#include "ast.hpp"
#include "tokens.hpp"

#include <memory>
#include <stdexcept>

namespace regex {
    Parser::Parser(std::unique_ptr<Tokenizer> tokenizer) : tokenizer_(std::move(tokenizer)) {}

    Expression Parser::Parse() {
        std::vector<std::unique_ptr<SubExpression>> subExpressions;
        if (tokenizer_->Match(TokenType::kStartAnchor)) {
            subExpressions.push_back(std::make_unique<StartAnchor>());
        }
        while (tokenizer_->Peak() != TokenType::kEnd) {
            if (tokenizer_->Match(TokenType::kEndAnchor)) {
                if (tokenizer_->Peak() != TokenType::kEnd) {
                    throw std::runtime_error("Parse end anchor not followed by EOF");
                }
                subExpressions.push_back(std::make_unique<EndAnchor>());
                break;
            }
            subExpressions.push_back(std::move(ParseSubExpression()));
        }
        Expression expression(std::move(subExpressions));
        return expression;
    }

    std::unique_ptr<SubExpression> Parser::ParseSubExpression() {
        std::unique_ptr<SubExpression> subExpression;
        if (tokenizer_->Match(TokenType::kDigit)) {
            subExpression = std::make_unique<Digit>();
        } else if (tokenizer_->Match(TokenType::kWord)) {
            subExpression = std::make_unique<Word>();
        } else if (tokenizer_->Match(TokenType::kDot)) {
            subExpression = std::make_unique<Wildcard>();
        } else if (tokenizer_->Peak() == TokenType::kLiteral) {
            subExpression = std::make_unique<Literal>(tokenizer_->GetNextToken().GetPayload());
        } else if (tokenizer_->Match(TokenType::kLeftBracket)) {
            auto isNegativeGroup = tokenizer_->Match(TokenType::kStartAnchor);
            std::vector<Literal> literals;
            bool foundRightBracket = false;
            while (tokenizer_->Peak() != TokenType::kEnd) {
                if (tokenizer_->Match(TokenType::kRightBracket)) {
                    foundRightBracket = true;
                    break;
                }
                if (tokenizer_->Peak() != TokenType::kLiteral) {
                    throw std::runtime_error("ParseSubExpression group non literal");
                }
                literals.push_back(Literal(tokenizer_->GetNextToken().GetPayload()));
            }
            if (!foundRightBracket) {
                throw std::runtime_error("ParseSubExpression group non rbracket");  
            }
            if (isNegativeGroup) {
                subExpression = std::make_unique<NegativeGroup>(std::move(literals));
            } else {
                subExpression = std::make_unique<PositiveGroup>(std::move(literals));
            }
        } else if (tokenizer_->Match(TokenType::kLeftBrace)) {
            std::vector<std::unique_ptr<SubExpression>> subExpressionsLeft;
            while (tokenizer_->Peak() != TokenType::kDivider
                    && tokenizer_->Peak() != TokenType::kEnd) {
                subExpressionsLeft.push_back(ParseSubExpression());
            }
            if (!tokenizer_->Match(TokenType::kDivider)) {
                throw std::runtime_error("ParseSubExpression alternation divider");  
            }
            std::vector<std::unique_ptr<SubExpression>> subExpressionsRight;
            while (tokenizer_->Peak() != TokenType::kRightBrace
                    && tokenizer_->Peak() != TokenType::kEnd) {
                subExpressionsRight.push_back(ParseSubExpression());
            }
            if (!tokenizer_->Match(TokenType::kRightBrace)) {
                throw std::runtime_error("ParseSubExpression alternation end");  
            }
            subExpression = std::make_unique<Alternation>(
                std::move(subExpressionsLeft),
                std::move(subExpressionsRight));
        }
        if (tokenizer_->Match(TokenType::kPlus)) {
            subExpression = std::make_unique<OnePlus>(std::move(subExpression));
        } else if (tokenizer_->Match(TokenType::kQuestion)) {
            subExpression = std::make_unique<ZeroPlus>(std::move(subExpression));
        }
        return subExpression;
    }
}
