#pragma once

#include <vector>

namespace regex {
    class AbstractSyntaxTree {
    public:

    private:
        StartAnchor startAnchor_;
        Expression expression_;
        EndAnchor endAnchor_;
    };

    class StartAnchor {};
    class EndAnchor {};
    
    class Expression {
    public:
        Expression(std::vector<SubExpression> subExpressions);
    private:
        std::vector<SubExpression> subExpressions_;
    };

    class SubExpression {
    public:
        ~SubExpression() {}
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
        PositiveGroup(const std::string& literals);
    private:
        std::string<char> literals_;
    };

    class NegativeGroup : public SubExpression {
    public:
        NegativeGroup(const std::string& literals);
    private:
        std::string<char> literals_;
    };

    class Alternation : public SubExpression {
        Alternation(std::vector<SubExpression> left,
        std::vector<SubExpression> right);
    private:
        std::vector<SubExpression> left_;
        std::vector<SubExpression> right_;
    };

    class OnePlus : public SubExpression {
    public:
        OnePlus(SubExpression expression);
    private:
        SubExpression expression_;
    };

    class ZeroPlus : public SubExpression {
    public:
        ZeroPlus(SubExpression expression);
    private:
        SubExpression expression_;
    };

    class Wildcard : public SubExpression {};
}