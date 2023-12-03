#include <vector>
#include <set>
#include <string>
#include "IRVisitor.h"

// using namespace std;

using std::vector;
using std::string;
using std::set;

std::any IRVisitor::visitFile(ExprParser::FileContext *context) {
  for (auto function : context->fun()) {
    function->accept(this);
  }
  context->prog()->accept(this);
  return std::any();
}

std::any IRVisitor::visitProg(ExprParser::ProgContext *ctx) {
  ctx->statements()->accept();
  return std::any();
}

std::any IRVisitor::visitExpr(ExprParser::ExprContext *ctx) {
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

std::any IRVisitor::visitStmt(ExprParser::StmtContext *ctx) {
  if (ctx->assign != nullptr) {
    return visitAssignStmt(ctx);
  } else if (ctx->printexp != nullptr) {
    return visitPrintStmt(ctx);
  } else if (ctx->execute != nullptr) {
    return visitExecuteStmt(ctx);
  } else if (ctx->declare_ident != nullptr) {
    return visitDeclareStmt(ctx);
  }
  throw std::runtime_error("Unknown expression: " + ctx->getText() + " !\n");
  return std::any();
}

template <typename T>
bool check_unique(std::vector<T> vec){
  set<T> unique_elements(vec.begin(), vec.end());
  return unique_elements.size() == vec.size();
}

std::any IRVisitor::visitFun(ExprParser::FunContext *context) {
  string func_name = context->ident->getText();
  vector<string> args = std::any_cast<vector<string>>(context->arguments->accept(this));
  if (!check_unique(args)) {
    throw std::runtime_error("Some argument appears in definition of " + func_name + " multiple times!\n");
  }
  llvm::ArrayRef<llvm::Type*> arguments(std::vector<llvm::Type*>(args.size(), Builder.getInt32Ty()));

  llvm::FunctionType* func_type = llvm::FunctionType::get(Builder.getInt32Ty(), arguments, false);
  llvm::Function* func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, func_name, TheModule);
  llvm::BasicBlock* func_block = llvm::BasicBlock::Create(TheContext, func_name + "bb", func);
  Builder.SetInsertPoint(func_block);
  
  context->statements()->accept(this);

  NamedFunctions[func_name] = func;
  return std::any();
}

std::any IRVisitor::visitIdents(ExprParser::IdentsContext *context) {
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

std::any IRVisitor::visitExprs(ExprParser::ExprsContext *context) {
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

std::any IRVisitor::visitPrintStmt(ExprParser::StmtContext *ctx) {
  std::cout << "> " << ctx->getText() << '\n';
  std::string output = "";
  auto expr = ctx->printexp->accept(this);
  if (expr.has_value()) {
    output = std::any_cast<Printable>(expr).str;
  }
  std::cout << output << '\n';
  return std::any();
}

// For now assign is declare and assign
std::any IRVisitor::visitAssignStmt(ExprParser::StmtContext *ctx) {
  std::cout << "> " << ctx->getText() << '\n';
  auto variable_name = ctx->ident->getText();
  auto variable_value = std::any_cast<Printable>(ctx->assign->accept(this));
  memory.Declare(variable_name, variable_value);
  return std::any();
}

std::any IRVisitor::visitExecuteStmt(ExprParser::StmtContext *ctx) {
  std::cout << "> " << ctx->getText() << '\n';
  ctx->execute->accept(this);
  return std::any();
}

std::any IRVisitor::visitDeclareStmt(ExprParser::StmtContext *ctx)
{
  llvm::AllocaInst* value_alloca = Builder.CreateAlloca(Builder.getInt32Ty());
  NamedVariables[ctx->declare_ident->getText()] = value_alloca;
  return std::any();
}

std::any IRVisitor::visitNumberExpr(ExprParser::ExprContext *ctx) {
  return Printable(std::stoi(ctx->value->getText()), ctx->value->getText());
}

std::any IRVisitor::visitBraceExpr(ExprParser::ExprContext *ctx) {
  return ctx->exp->accept(this);
}

std::any IRVisitor::visitVarIdentExpr(ExprParser::ExprContext *ctx) {
  auto name = ctx->variable_ident->getText();
  return memory.Get(name);
}

std::any IRVisitor::visitAddExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) +
         std::any_cast<Printable>(ctx->right->accept(this));
}

std::any IRVisitor::visitSubExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) -
         std::any_cast<Printable>(ctx->right->accept(this));
}

std::any IRVisitor::visitFunExpr(ExprParser::ExprContext *ctx) {
  // for (auto statement : _functions.at(ctx->function_ident->getText())->stmt()) {
  //   statement->accept(this);
  // }
  return _functions.at(ctx->function_ident->getText())->return_expr->accept(this);
}

std::any IRVisitor::visitMulExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) *
         std::any_cast<Printable>(ctx->right->accept(this));
}

std::any IRVisitor::visitDivExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) /
         std::any_cast<Printable>(ctx->right->accept(this));
}