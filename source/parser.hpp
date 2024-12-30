#pragma once

#include <memory>

namespace regex {
    class Parser {
    public:
        void Parser(std::unique_ptr<Tokenizer> tokenizer);
    private:
        std::unique_ptr<Tokenizer> tokenizer;
    };
}
