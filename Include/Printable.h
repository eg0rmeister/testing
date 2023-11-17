#pragma once

#include <any>
#include <string>

struct Printable {
  /// @brief Wrapper around std::any to print variables of any type
  Printable();
  Printable(std::any value, std::string str);
  std::any value;
  std::string str;
};

Printable operator+(const Printable &lhs, const Printable &rhs);

Printable operator-(const Printable &lhs, const Printable &rhs);

Printable operator*(const Printable &lhs, const Printable &rhs);

Printable operator/(const Printable &lhs, const Printable &rhs);