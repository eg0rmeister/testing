#include "PrintVisitor.h"

#include <iostream>
#include <string>

std::any PrintVisitor::visitFile(ExprParser::FileContext* context) {
  std::cout << "File" << std::endl;
  ++tab_level_;
  for (auto function : context->fun()) {
    function->accept(this);
  }
  context->prog()->accept(this);
  --tab_level_;
  return std::any();
}

std::any PrintVisitor::visitProg(ExprParser::ProgContext* ctx) {
  std::cout << "Main" << std::endl;
  ctx->statements()->accept(this);
  return std::any();
}

std::any PrintVisitor::visitExpr(ExprParser::ExprContext* ctx) {
  auto tab = getTab(tab_level_);
  std::cout << tab << "Expr: ";
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
  auto tab = getTab(tab_level_);
  std::cout << tab << "Stmt: ";
  if (ctx->assign != nullptr) {
    return visitAssignStmt(ctx);
  } else if (ctx->printexp != nullptr) {
    return visitPrintStmt(ctx);
  } else if (ctx->execute != nullptr) {
    return visitExecuteStmt(ctx);
  } else if (ctx->ifexp != nullptr) {
    return visitIfStmt(ctx);
  } else if (ctx->while_condition != nullptr) {
    return visitWhileStmt(ctx);
  } else if (ctx->getText() == "break") {
    return std::any();
  }
  throw std::runtime_error("Unknown expression: " + ctx->getText() + " !\n");
  return std::any();
}

std::any PrintVisitor::visitFun(ExprParser::FunContext* context) {
  std::cout << "Fun" << std::endl;
  tabUp();
  context->statements()->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitIdents(ExprParser::IdentsContext* context) {
  std::cout << "Idents" << std::endl;
  return std::any();
}

std::any PrintVisitor::visitExprs(ExprParser::ExprsContext* context) {
  std::cout << "Exprs" << std::endl;
  tabUp();
  for (auto expr : context->expr()) {
    expr->accept(this);
  }
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitStatements(ExprParser::StatementsContext* context) {
  auto tab = getTab(tab_level_);
  std::cout << tab << "Statements" << std::endl;
  for (auto statement : context->stmt()) {
    statement->accept(this);
  }
  return std::any();
}

std::any PrintVisitor::visitPrintStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Print" << std::endl;
  tabUp();
  ctx->printexp->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitAssignStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Assign" << std::endl;
  tabUp();
  ctx->assign->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitExecuteStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Execute" << std::endl;
  tabUp();
  ctx->execute->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitIfStmt(ExprParser::StmtContext* ctx) {
  std::cout << "If" << std::endl;
  tabUp();
  auto tab = getTab(tab_level_);
  std::cout << tab << "If statement condition" << std::endl;
  tabUp();
  ctx->ifexp->accept(this);
  tabDown();
  std::cout << tab << "If statement body" << std::endl;
  tabUp();
  ctx->ifstmt->accept(this);
  tabDown();
  if (ctx->elsestmt != nullptr) {
    std::cout << tab << "If statement else body" << std::endl;
    tabUp();
    ctx->elsestmt->accept(this);
    tabDown();
  }
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitWhileStmt(ExprParser::StmtContext *ctx) {
  std::cout << "While" << std::endl;
  tabUp();
  auto tab = getTab(tab_level_);
  std::cout << tab << "While condition" << std::endl;
  tabUp();
  ctx->while_condition->accept(this);
  tabDown();
  std::cout << tab << "While statement" << std::endl;
  tabUp();
  ctx->whilestmts->accept(this);
  tabDown();
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitNumberExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Number " << ctx->getText() << std::endl;
  return std::any();
}

std::any PrintVisitor::visitBraceExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Brace" << std::endl;
  tabUp();
  ctx->exp->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitVarIdentExpr(ExprParser::ExprContext* ctx) {
  std::cout << "VarIdent " << ctx->getText() << std::endl;
  return std::any();
}

std::any PrintVisitor::visitDivExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Div" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitMulExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Mul" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitAddExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Add" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitSubExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Sub" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitFunExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Fun" << std::endl;
  return std::any();
}

std::any PrintVisitor::visitMoreExpr(ExprParser::ExprContext* ctx) {
  std::cout << "More" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitLessExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Less" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Equal" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitNotEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "NotEqual" << std::endl;
  std::cout << "NotEqual" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitLessOrEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "LessOrEqual" << std::endl;
  std::cout << "LessOrEqual" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::any PrintVisitor::visitMoreOrEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "MoreOrEqual" << std::endl;
  tabUp();
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown();
  return std::any();
}

std::string PrintVisitor::getTab(size_t tab_level)
{
  return std::string(tab_level, '\t');
}

void PrintVisitor::tabUp() {
  ++tab_level_;
}

void PrintVisitor::tabDown() {
  --tab_level_;
}
