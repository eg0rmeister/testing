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
  string func_name = "main";
  llvm::FunctionType* func_type = llvm::FunctionType::get(Builder.getInt32Ty(), false);
  llvm::Function* func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, func_name, TheModule);
  llvm::BasicBlock* func_block = llvm::BasicBlock::Create(TheContext, func_name + "bb", func);
  Builder.SetInsertPoint(func_block);
  
  ctx->statements()->accept(this);
  Builder.CreateRet(llvm::ConstantInt::get(Builder.getInt32Ty(), llvm::APInt(32, 0, true)));
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
  vector<string> ret;
  for (auto ident : context->IDENT()) {
    ret.push_back(ident->getText());
  }
  return ret;
}

std::any IRVisitor::visitExprs(ExprParser::ExprsContext *context) {
  vector<llvm::Value*> ret;
  for (auto expr : context->expr()) {
    ret.push_back(std::any_cast<llvm::Value*>(expr->accept(this)));
  }
  return ret;
}

void IRVisitor::printIR() {
  TheModule.print(llvm::outs(), nullptr);
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

// For now assign is assign only
std::any IRVisitor::visitAssignStmt(ExprParser::StmtContext *ctx) {
  string variable_name = ctx->ident->getText();
  llvm::Value* value = std::any_cast<llvm::Value*>(ctx->assign->accept(this));
  llvm::AllocaInst* alloca_inst = NamedVariables.at(variable_name);
  Builder.CreateStore(value, alloca_inst);
  return std::any();
}

std::any IRVisitor::visitExecuteStmt(ExprParser::StmtContext *ctx) {
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
  string func_name = ctx->function_ident->getText();
  vector<llvm::Value*> arguments = std::any_cast<vector<llvm::Value*>>(ctx->arguments->accept(this));
  return Builder.CreateCall(NamedFunctions.at(func_name), arguments);
}

std::any IRVisitor::visitMulExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) *
         std::any_cast<Printable>(ctx->right->accept(this));
}

std::any IRVisitor::visitDivExpr(ExprParser::ExprContext *ctx) {
  return std::any_cast<Printable>(ctx->left->accept(this)) /
         std::any_cast<Printable>(ctx->right->accept(this));
}