#include "ast.hpp"
#include "tokens.hpp"
#include "tokenizer.hpp"

namespace regex {
    Literal::Literal(char c) : c_(c) {}

    PositiveGroup::PositiveGroup(std::vector<Literal>&& literals) : literals_(std::move(literals)) {}
    NegativeGroup::NegativeGroup(std::vector<Literal>&& literals) : literals_(std::move(literals)) {}

    Alternation::Alternation(
        std::vector<std::unique_ptr<SubExpression>>&& left,
        std::vector<std::unique_ptr<SubExpression>>&& right) : left_(std::move(left)), right_(std::move(right)) {}

    Expression::Expression(std::vector<std::unique_ptr<SubExpression>>&& subExpressions) : subExpressions_(std::move(subExpressions)) {}

    OnePlus::OnePlus(std::unique_ptr<SubExpression> expresion) : expression_(std::move(expresion)) {}
    ZeroPlus::ZeroPlus(std::unique_ptr<SubExpression> expresion) : expression_(std::move(expresion)) {}
}