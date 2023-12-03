#include <stdexcept>
#include "Printable.h"

Printable operator+(const Printable &lhs, const Printable &rhs);

Printable operator-(const Printable &lhs, const Printable &rhs);

Printable operator*(const Printable &lhs, const Printable &rhs);

Printable operator/(const Printable &lhs, const Printable &rhs);

Printable::Printable() : Printable(std::any(), std::string()) {}

Printable::Printable(std::any value, std::string str)
    : value(value), str(str) {}

Printable operator+(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) + std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator+ for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator-(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) - std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator- for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator*(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) * std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator* for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator/(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) / std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator/ for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator<(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) < std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator< for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator>(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) > std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator> for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator<=(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) <= std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator<= for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator>=(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) >= std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator>= for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator==(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) == std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator== for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}

Printable operator!=(const Printable &lhs, const Printable &rhs) {
  if (lhs.value.type() == typeid(int) && rhs.value.type() == typeid(int)) {
    int result = std::any_cast<int>(lhs.value) != std::any_cast<int>(rhs.value);
    return {result, std::to_string(result)};
  }
  throw std::runtime_error("No operator!= for these operands: " + lhs.str + " " +
                           rhs.str + " !");
}
