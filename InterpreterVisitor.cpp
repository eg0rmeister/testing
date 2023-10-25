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
    return visitNumberExpr(ctx->value);
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
  throw std::runtime_error("Unknown expression!");
  return std::any();
}

std::any InterpreterVisitor::visitPrintStmt(ExprParser::StmtContext *ctx) {
  std::cout << "> " << ctx->getText() << '\n';
  std::string output = "";
  auto expr = ctx->printexp->accept(this);
  if (expr.has_value()) {
    output = std::any_cast<std::string>(expr);
  }
  std::cout << output << '\n';
  return std::any();
}

std::any InterpreterVisitor::visitAssignStmt(ExprParser::StmtContext *ctx) {
  std::cout << "> " << ctx->getText() << '\n';
  _variables[ctx->ident->getText()] = ctx->assign->accept(this);
  return std::any();
}

int InterpreterVisitor::visitNumberExpr(antlr4::Token *number)
{
  return std::stoi(number->getText());
}
