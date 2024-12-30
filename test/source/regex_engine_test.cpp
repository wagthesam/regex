#include <catch2/catch_test_macros.hpp>

#include "tokenizer.hpp"

TEST_CASE("test tokenize")
{
  auto tokenizer = regex::Tokenizer("^")
  REQUIRE(toknizer.GetNextToken().GetTokenType() == regex::TokenType::kStartAnchor);
}

TEST_CASE("test eof")
{
  auto tokenizer = regex::Tokenizer("")
  REQUIRE(toknizer.GetNextToken().GetTokenType() == regex::TokenType::kEnd);
}
