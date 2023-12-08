#include "PrintVisitor.h"

#include <iostream>
#include <string>

PrintVisitor::PrintVisitor() {
  root_ = new ASTNode("root");
  current_node_ = root_;
}

PrintVisitor::~PrintVisitor() {
  deleteASTNode(root_);
}

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
  tabUp("Fun");
  context->statements()->accept(this);
  tabDown("Fun");
  return std::any();
}

std::any PrintVisitor::visitIdents(ExprParser::IdentsContext* context) {
  std::cout << "Idents" << std::endl;
  return std::any();
}

std::any PrintVisitor::visitExprs(ExprParser::ExprsContext* context) {
  std::cout << "Exprs" << std::endl;
  tabUp("Exprs");
  for (auto expr : context->expr()) {
    expr->accept(this);
  }
  tabDown("Exprs");
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
  tabUp("Print");
  ctx->printexp->accept(this);
  tabDown("Print");
  return std::any();
}

std::any PrintVisitor::visitAssignStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Assign" << std::endl;
  tabUp("Assign");
  ctx->assign->accept(this);
  tabDown("Assign");
  return std::any();
}

std::any PrintVisitor::visitExecuteStmt(ExprParser::StmtContext* ctx) {
  std::cout << "Execute" << std::endl;
  tabUp("Execute");
  ctx->execute->accept(this);
  tabDown("Execute");
  return std::any();
}

std::any PrintVisitor::visitIfStmt(ExprParser::StmtContext* ctx) {
  std::cout << "If" << std::endl;
  tabUp("IfStmt");
  auto tab = getTab(tab_level_);
  std::cout << tab << "If statement condition" << std::endl;
  tabUp("IfStmtCond");
  ctx->ifexp->accept(this);
  tabDown("IfStmtCond");
  std::cout << tab << "If statement body" << std::endl;
  tabUp("If statement body");
  ctx->ifstmt->accept(this);
  tabDown("If statement body");
  if (ctx->elsestmt != nullptr) {
    std::cout << tab << "If statement else body" << std::endl;
    tabUp("IfStmtElseCond");
    ctx->elsestmt->accept(this);
    tabDown("IfStmtElseCond");
  }
  tabDown("IfStmt");
  return std::any();
}

std::any PrintVisitor::visitWhileStmt(ExprParser::StmtContext* ctx) {
  std::cout << "While" << std::endl;
  tabUp("While");
  auto tab = getTab(tab_level_);
  std::cout << tab << "While condition" << std::endl;
  tabUp("WhileCond");
  ctx->while_condition->accept(this);
  tabDown("WhileCond");
  std::cout << tab << "While statement" << std::endl;
  tabUp("While statement");
  ctx->whilestmts->accept(this);
  tabDown("While statement");
  tabDown("While");
  return std::any();
}

std::any PrintVisitor::visitNumberExpr(ExprParser::ExprContext* ctx) {
  tabUp("Number");
  std::cout << "Number " << ctx->getText() << std::endl;
  tabDown("Number");
  return std::any();
}

std::any PrintVisitor::visitBraceExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Brace" << std::endl;
  tabUp("Brace");
  ctx->exp->accept(this);
  tabDown("Brace");
  return std::any();
}

std::any PrintVisitor::visitVarIdentExpr(ExprParser::ExprContext* ctx) {
  tabUp("VarIdent");
  std::cout << "VarIdent " << ctx->getText() << std::endl;
  tabDown("VarIdent");
  return std::any();
}

std::any PrintVisitor::visitDivExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Div" << std::endl;
  tabUp("Div");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("Div");
  return std::any();
}

std::any PrintVisitor::visitMulExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Mul" << std::endl;
  tabUp("Mul");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("Mul");
  return std::any();
}

std::any PrintVisitor::visitAddExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Add" << std::endl;
  tabUp("Add");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("Add");
  return std::any();
}

std::any PrintVisitor::visitSubExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Sub" << std::endl;
  tabUp("Sub");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("Sub");
  return std::any();
}

std::any PrintVisitor::visitFunExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Fun" << std::endl;
  return std::any();
}

std::any PrintVisitor::visitMoreExpr(ExprParser::ExprContext* ctx) {
  std::cout << "More" << std::endl;
  tabUp("More");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("More");
  return std::any();
}

std::any PrintVisitor::visitLessExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Less" << std::endl;
  tabUp("Less");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("Less");
  return std::any();
}

std::any PrintVisitor::visitEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "Equal" << std::endl;
  tabUp("Equal");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("Equal");
  return std::any();
}

std::any PrintVisitor::visitNotEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "NotEqual" << std::endl;
  std::cout << "NotEqual" << std::endl;
  tabUp("NotEqual");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("NotEqual");
  return std::any();
}

std::any PrintVisitor::visitLessOrEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "LessOrEqual" << std::endl;
  std::cout << "LessOrEqual" << std::endl;
  tabUp("LessOrEqual");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("LessOrEqual");
  return std::any();
}

std::any PrintVisitor::visitMoreOrEqualExpr(ExprParser::ExprContext* ctx) {
  std::cout << "MoreOrEqual" << std::endl;
  tabUp("MoreOrEqual");
  ctx->left->accept(this);
  ctx->right->accept(this);
  tabDown("MoreOrEqual");
  return std::any();
}

std::string PrintVisitor::getTab(size_t tab_level) {
  return std::string(tab_level, '\t');
}

void PrintVisitor::tabUp() { ++tab_level_; }

void PrintVisitor::tabDown() { --tab_level_; }

void PrintVisitor::tabUp(std::string node_name) {
  tabUp();
  ASTNode* node = new ASTNode(node_name);
  node->parent = current_node_;
  current_node_->children.push_back(node);
  current_node_ = node;
}

void PrintVisitor::tabDown(std::string node_name) {
  tabDown();
  current_node_ = current_node_->parent;
}

void PrintVisitor::deleteASTNode(ASTNode *node)
{
  if (node == nullptr) {
    return;
  }
  ASTNode* parent = node->parent;
  node->parent = nullptr;
  for (auto child : node->children) {
    deleteASTNode(child);
  }
  delete node;
}

ASTNode::ASTNode(std::string label) : label(label) {}
