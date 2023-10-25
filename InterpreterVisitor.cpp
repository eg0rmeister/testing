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
	if (ctx->assign != nullptr) {
		std::cout << "AssignStmt: " << ctx->getText() << '\n';
		visitExpr(ctx->expr());
	} else if (ctx->printexp != nullptr) {
		std::cout << "PrintStmt: " << ctx->getText() << '\n';
		visitExpr(ctx->expr());
	} else {
		std::cout << "UnknownStmt: " << ctx->getText() << '\n';
	}
  
  return std::any();
}
