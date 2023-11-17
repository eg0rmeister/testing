#include "InterpreterVisitor.h"

using namespace std;

// std::any InterpreterVisitor::visitFile(ExprParser::ProgContext *ctx) {
//   return std::any();
// }

std::any InterpreterVisitor::visitFile(ExprParser::FileContext *context) {
  for (auto function : context->fun()) {
    function->accept(this);
  }
  context->prog()->accept(this);
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
  if (ctx->variable_ident != nullptr) {
    return visitVarIdentExpr(ctx);
  }
  if (ctx->function_ident != 0) {
    return visitFunExpr(ctx);
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
  } else if (ctx->execute != nullptr) {
    return visitExecuteStmt(ctx);
  }
  throw std::runtime_error("Unknown expression: " + ctx->getText() + " !\n");
  return std::any();
}

std::any InterpreterVisitor::visitFun(ExprParser::FunContext *context) {
  _functions[context->ident->getText()] = context;
  return std::any();
}

// TODO: Implement real idents
std::any InterpreterVisitor::visitIdents(ExprParser::IdentsContext *context) {
  if (context->ident == nullptr) {
    return std::vector<string>();
  }
  if (context->rest == nullptr) {
    std::vector<string> ret;
    ret.push_back(context->ident->getText());
    return ret;
  }
  std::vector<string> ret =
      std::any_cast<std::vector<string>>(context->rest->accept(this));
  ret.push_back(context->ident->getText());
  return ret;
}

// TODO: Implement real exprs
std::any InterpreterVisitor::visitExprs(ExprParser::ExprsContext *context) {
  if (context->expression == nullptr) {
    return std::vector<int>();
  }
  if (context->rest == nullptr) {
    std::vector<int> ret;
    ret.push_back(std::any_cast<int>(context->expression->accept(this)));
    return ret;
  }
  std::vector<int> ret =
      std::any_cast<std::vector<int>>(context->rest->accept(this));
  ret.push_back(std::any_cast<int>(context->expression->accept(this)));
  return ret;
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

std::any InterpreterVisitor::visitExecuteStmt(ExprParser::StmtContext *ctx) {
  std::cout << "> " << ctx->getText() << '\n';
  ctx->execute->accept(this);
  return std::any();
}

std::any InterpreterVisitor::visitNumberExpr(ExprParser::ExprContext *ctx) {
  return Printable(std::stoi(ctx->value->getText()), ctx->value->getText());
}

std::any InterpreterVisitor::visitBraceExpr(ExprParser::ExprContext *ctx) {
  return ctx->exp->accept(this);
}

std::any InterpreterVisitor::visitVarIdentExpr(ExprParser::ExprContext *ctx) {
  auto name = ctx->variable_ident->getText();
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

std::any InterpreterVisitor::visitFunExpr(ExprParser::ExprContext *ctx) {
  for (auto statement : _functions.at(ctx->function_ident->getText())->stmt()) {
    statement->accept(this);
  }
  return _functions.at(ctx->function_ident->getText())->return_expr->accept(this);
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
