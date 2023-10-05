#include "Token.h"

Token::Token(std::string lexem, size_t token) : _lexem(lexem), _token(token) {}

std::string Token::Type() const { return TokenTOString(_token); }

inline std::string TokenTOString(size_t token) {
  std::string token_str = "ERROR";
  switch (token) {
    case MINUS:
      token_str = "MINUS";
      break;
    case NUMBER:
      token_str = "NUMBER";
      break;
    case PLUS:
      token_str = "PLUS";
      break;
    case STR:
      token_str = "STR";
      break;
    case TYPE:
      token_str = "TYPE";
      break;
    case VAR:
      token_str = "VAR";
      break;

    default:
      break;
  }
  return token_str;
}
