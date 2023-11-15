#include "InterpreterVisitor.h"

using namespace std;

std::any InterpreterVisitor::visitFile(ExprParser::ProgContext *ctx) {
  return std::any();
}

std::any InterpreterVisitor::visitProg(ExprParser::ProgContext *ctx) {
  for (auto statement : ctx->stmt()) {
    statement->accept(this);
  }
  return std::any();
}

std::any InterpreterVisitor::visitExpr(ExprParser::ExprContext *ctx) {
  if (ctx->value != nullptr) {
    return visitNumberExpr(ctx);
  }
  if (ctx->exp != nullptr) {
    return visitBraceExpr(ctx);
  }
  if (ctx->ident != nullptr) {
    return visitIdentExpr(ctx);
  }
  if (ctx->op->getText() == "+") {
    return visitAddExpr(ctx);
  }
  if (ctx->op->getText() == "-") {
    return visitSubExpr(ctx);
  }
  if (ctx->op->getText() == "*") {
    return visitMulExpr(ctx);
  }
  if (ctx->op->getText() == "/") {
    return visitDivExpr(ctx);
  }
  std::cout << "Expr: " << ctx->getText() << '\n';
  return std::any();
}

std::any InterpreterVisitor::visitStmt(ExprParser::StmtContext *ctx) {
  if (ctx->assign != nullptr) {
    return visitAssignStmt(ctx);
  } else if (ctx->printexp != nullptr) {
    return visitPrintStmt(ctx);
  }
  throw std::runtime_error("Unknown expression: " + ctx->getText() + " !\n");
  return std::any();
}

std::any InterpreterVisitor::visitPrintStmt(ExprParser::StmtContext *ctx) {
  std::cout << "> " << ctx->getText() << '\n';
  std::string output = "";
  auto expr = ctx->printexp->accept(this);
  if (expr.has_value()) {
    output = std::any_cast<Printable>(expr).str;
  }
  std::cout << output << '\n';
  return std::any();
}

std::any InterpreterVisitor::visitAssignStmt(ExprParser::StmtContext *ctx) {
  std::cout << "> " << ctx->getText() << '\n';
  auto variable_name = ctx->ident->getText();
  auto variable_value = std::any_cast<Printable>(ctx->assign->accept(this));
  _variables[variable_name] = variable_value;
  return std::any();
}

std::any InterpreterVisitor::visitNumberExpr(ExprParser::ExprContext *ctx) {
  return Printable(std::stoi(ctx->value->getText()), ctx->value->getText());
}

std::any InterpreterVisitor::visitBraceExpr(ExprParser::ExprContext *ctx) {
  return ctx->exp->accept(this);
}

std::any InterpreterVisitor::visitIdentExpr(ExprParser::ExprContext *ctx) {
  auto name = ctx->ident->getText();
  if (_variables.find(name) == _variables.end()) {
    throw std::runtime_error("Variable not found: " + name + " !\n");
  }
  return _variables[name];
}

Printable operator+(const Printable &lhs, const Printable &rhs);

std::any InterpreterVisitor::visitAddExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) +
         std::any_cast<Printable>(ctx->right->accept(this));
}

Printable operator-(const Printable &lhs, const Printable &rhs);

std::any InterpreterVisitor::visitSubExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) -
         std::any_cast<Printable>(ctx->right->accept(this));
}

Printable operator*(const Printable &lhs, const Printable &rhs);

std::any InterpreterVisitor::visitMulExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) *
         std::any_cast<Printable>(ctx->right->accept(this));
}

Printable operator/(const Printable &lhs, const Printable &rhs);

std::any InterpreterVisitor::visitDivExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) /
         std::any_cast<Printable>(ctx->right->accept(this));
}

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
