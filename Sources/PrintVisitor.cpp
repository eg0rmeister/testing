#include <string>
#include <iostream>
#include "PrintVisitor.h"

std::any PrintVisitor::visitFile(ExprParser::FileContext* context) {
  std::cout << "File" << std::endl;
  for (auto function : context->fun()) {
    function->accept(this);
  }
  context->prog()->accept(this);
  return std::any();
}

std::any PrintVisitor::visitProg(ExprParser::ProgContext* ctx) {
  std::cout << "Main" << std::endl;
  for (auto statement : ctx->stmt()) {
    statement->accept(this);
  }
  return std::any();
}

std::any PrintVisitor::visitExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Expr:";
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
  return std::any();
}

std::any PrintVisitor::visitStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Stmt: ";
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

std::any PrintVisitor::visitFun(ExprParser::FunContext* context) {
  std::cout << "Fun declaration";
  _functions[context->ident->getText()] = context;
  return std::any();
}
