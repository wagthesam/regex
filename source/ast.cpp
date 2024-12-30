#include "ast.hpp"

namespace regex {
    Literal::Literal(char c) : c_(c) {}

    PositiveGroup::PositiveGroup(const std::string& literals) : literals_(literals) {}
    NegativeGroup::NegativeGroup(const std::string& literals) : literals_(literals) {}

    Alternation::Alternation(std::vector<SubExpression> left, std::vector<SubExpression> right) : left_(left), right_(right) {}

    Expression::Expression(std::vector<SubExpression> subExpressions) : subExpressions_(subExpressions) {}

    OnePlus::OnePlus(SubExpression expresion) : expresion_(expresion) {}
    ZeroPlus::ZeroPlus(SubExpression expresion) : expresion_(expresion) {}
}