#pragma once

#include "tokenizer.hpp"
#include "ast.hpp"

#include <memory>

namespace regex {
    class Parser {
    public:
        Parser(std::unique_ptr<Tokenizer> tokenizer);
        [[nodiscard]] Expression Parse();
    private:
        [[nodiscard]] std::unique_ptr<SubExpression> ParseSubExpression();

        std::unique_ptr<Tokenizer> tokenizer_;
    };
}
