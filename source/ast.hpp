#pragma once

#include "tokens.hpp"

#include <vector>
#include <string>

namespace regex {

    class SubExpression {
    public:
        ~SubExpression() {}
    };

    class Expression {
    public:
        Expression(std::vector<std::unique_ptr<SubExpression>>&& subExpressions);
    private:
        std::vector<std::unique_ptr<SubExpression>> subExpressions_;
    };

    class Literal : public SubExpression {
    public:
        Literal(char c);
    private:
        char c_;
    };

    class Digit : public SubExpression {};

    class Word : public SubExpression {};

    class PositiveGroup : public SubExpression {
    public:
        PositiveGroup(std::vector<Literal>&& literals);
    private:
        std::vector<Literal> literals_;
    };

    class NegativeGroup : public SubExpression {
    public:
        NegativeGroup(std::vector<Literal>&& literals);
    private:
        std::vector<Literal> literals_;
    };

    class Alternation : public SubExpression {
    public:
        Alternation(
            std::vector<std::unique_ptr<SubExpression>>&& left,
            std::vector<std::unique_ptr<SubExpression>>&& right);
    private:
        std::vector<std::unique_ptr<SubExpression>> left_;
        std::vector<std::unique_ptr<SubExpression>> right_;
    };

    class OnePlus : public SubExpression {
    public:
        OnePlus(std::unique_ptr<SubExpression> expression);
    private:
        std::unique_ptr<SubExpression> expression_;
    };

    class ZeroPlus : public SubExpression {
    public:
        ZeroPlus(std::unique_ptr<SubExpression> expression);
    private:
        std::unique_ptr<SubExpression> expression_;
    };

    class Wildcard : public SubExpression {};

    class StartAnchor: public SubExpression {};
    class EndAnchor : public SubExpression {};
}