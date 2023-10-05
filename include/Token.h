#pragma once
#include <string>

enum Tokens { MINUS, NUMBER, PLUS, STR, TYPE, VAR };

std::string TokenTOString(size_t token);

class Token {
 public:
  Token(std::string lexem, size_t token);

 private:
  const std::string _lexem;
  const size_t _token;
};