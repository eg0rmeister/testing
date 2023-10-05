#pragma once
#include <string>

enum Tokens { MINUS, NUMBER, PLUS, STR, TYPE, VAR };

std::string TokenTOString(size_t token);

class Token {
 public:
  Token(std::string lexeme, size_t token);

  /// @brief Returns type of token
  /// @return std::string with name of token type - e.g "VAR"
  std::string Type() const;

 private:
  const std::string _lexeme;
  const size_t _token;
};