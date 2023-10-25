#include "InterpreterVisitor.h"

using namespace std;

std::any InterpreterVisitor::visitFile(ExprParser::ProgContext *ctx) {
  return true;
}

std::any InterpreterVisitor::visitProg(ExprParser::ProgContext *ctx) {
  for (auto statement : ctx->stmt()) {
    statement->accept(this);
  }
	return std::any();
}

std::any InterpreterVisitor::visitExpr(ExprParser::ExprContext *ctx) {
  std::cout << "Expr: " << ctx->getText() << '\n';
  return std::any();
}

std::any InterpreterVisitor::visitStmt(ExprParser::StmtContext *ctx) {
  std::cout << "Stmt: " << ctx->getText() << '\n';
  return std::any();
}
