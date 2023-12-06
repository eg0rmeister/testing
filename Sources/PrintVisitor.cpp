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
  ctx->statements()->accept(this);
  return std::any();
}

std::any PrintVisitor::visitExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Expr: ";
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
  if (ctx->op->getText() == ">") {
    return visitMoreExpr(ctx);
  }
  if (ctx->op->getText() == "<") {
    return visitLessExpr(ctx);
  }
  if (ctx->op->getText() == ">=") {
    return visitMoreOrEqualExpr(ctx);
  }
  if (ctx->op->getText() == "<=") {
    return visitLessOrEqualExpr(ctx);
  }
  if (ctx->op->getText() == "==") {
    return visitEqualExpr(ctx);
  }
  if (ctx->op->getText() == "!=") {
    return visitNotEqualExpr(ctx);
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
  } else if (ctx->ifexp != nullptr) {
    return visitIfStmt(ctx);
  }
  throw std::runtime_error("Unknown expression: " + ctx->getText() + " !\n");
  return std::any();
}

std::any PrintVisitor::visitFun(ExprParser::FunContext* context) {
  std::cout << "Fun" << std::endl;
  context->statements()->accept(this);
  return std::any();
}

std::any PrintVisitor::visitIdents(ExprParser::IdentsContext* context) {
  std::cout << "Idents" << std::endl;
  return std::any();
}

std::any PrintVisitor::visitExprs(ExprParser::ExprsContext* context) {
  std::cout << "Exprs" << std::endl;
  for (auto expr : context->expr()) {
    expr->accept(this);
  }
  return std::any();
}

std::any PrintVisitor::visitStatements(ExprParser::StatementsContext* context) {
  std::cout << "Statements" << std::endl;
  for (auto statement : context->stmt()) {
    statement->accept(this);
  } 
  return std::any();
}

std::any PrintVisitor::visitPrintStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Print" << std::endl;
  ctx->printexp->accept(this);
  return std::any();
}

std::any PrintVisitor::visitAssignStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Assign" << std::endl;
  ctx->assign->accept(this);
  return std::any();
}

std::any PrintVisitor::visitExecuteStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Execute" << std::endl;
  ctx->execute->accept(this);
  return std::any();
}

std::any PrintVisitor::visitIfStmt(ExprParser::StmtContext* ctx) {
  std::cout << "If statement" << std::endl;
  ctx->ifstmt->accept(this);
  std::cout << "Else statement" << std::endl;
  ctx->elsestmt->accept(this);
  return std::any();
}

std::any PrintVisitor::visitNumberExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Number" << std::endl;
  return std::any();
}

std::any PrintVisitor::visitBraceExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Brace" << std::endl;
  ctx->exp->accept(this);
  return std::any();
}

std::any PrintVisitor::visitVarIdentExpr(ExprParser::ExprContext* ctx) {
  std::cout << "VarIdent" << std::endl;
  return std::any();
}

std::any PrintVisitor::visitDivExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Div" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitMulExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Mul" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitAddExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Add" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitSubExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Sub" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitFunExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Fun" << std::endl;
  return std::any();
}

std::any PrintVisitor::visitMoreExpr(ExprParser::ExprContext* ctx) {
  std::cout << "More" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitLessExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Less" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Equal" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitNotEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "NotEqual" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitLessOrEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "LessOrEqual" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}

std::any PrintVisitor::visitMoreOrEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "MoreOrEqual" << std::endl;
  ctx->left->accept(this);
  ctx->right->accept(this);
  return std::any();
}
