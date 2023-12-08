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
  current_function = func;
  
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

std::any IRVisitor::visitStmt(ExprParser::StmtContext *ctx) {
  if (ctx->assign != nullptr) {
    return visitAssignStmt(ctx);
  } else if (ctx->printexp != nullptr) {
    return visitPrintStmt(ctx);
  } else if (ctx->execute != nullptr) {
    return visitExecuteStmt(ctx);
  } else if (ctx->declare_ident != nullptr) {
    return visitDeclareStmt(ctx);
  } else if (ctx->ifexp != nullptr) {
    return visitIfStmt(ctx);
  }
  throw std::runtime_error("Unknown expression: " + ctx->getText() + " !\n");
  return std::any();
}

template <typename T>
bool check_unique(std::vector<T> vec){
  set<T> unique_elements(vec.begin(), vec.end());
  return unique_elements.size() == vec.size();
}

// This needs argument work. (will probably come with symbol table)
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
  current_function = func;
  
  context->statements()->accept(this);
  if (context->return_expr == nullptr) {
    Builder.CreateRet(llvm::ConstantInt::get(Builder.getInt32Ty(), llvm::APInt(32, 0, true)));
  } else {
    Builder.CreateRet(std::any_cast<llvm::Value*>(context->return_expr->accept(this)));
  }

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
  // Try to get existing printf function. If it is not declared, declare one
  llvm::Function* printf_func = TheModule.getFunction("printf");
  if (printf_func == nullptr){
    llvm::FunctionType* printf_type = llvm::FunctionType::get(
      Builder.getInt32Ty(),
      {Builder.getInt8PtrTy()},
      true
    );
    printf_func = llvm::Function::Create(
      printf_type,
      llvm::Function::ExternalLinkage,
      "printf",
      TheModule
    );
  }
  string int_string = "%d\n";
  auto fmt_int = llvm::ConstantDataArray::getString(TheContext, int_string);
  auto string_int_alloca = Builder.CreateAlloca(fmt_int->getType());
  auto string_int_value = Builder.CreateStore(fmt_int, string_int_alloca);
  auto formatted_int_string = Builder.CreateBitCast(
    string_int_alloca,
    Builder.getInt8PtrTy()
  );

  Builder.CreateCall(
    printf_func,
    {
      formatted_int_string, 
      std::any_cast<llvm::Value*>(ctx->printexp->accept(this))
    }
  );
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

// No check for redeclaration now
std::any IRVisitor::visitDeclareStmt(ExprParser::StmtContext *ctx)
{
  llvm::AllocaInst* value_alloca = Builder.CreateAlloca(Builder.getInt32Ty());
  NamedVariables[ctx->declare_ident->getText()] = value_alloca;
  return std::any();
}

std::any IRVisitor::visitIfStmt(ExprParser::StmtContext *ctx) {
  llvm::BasicBlock* if_block = llvm::BasicBlock::Create(TheContext, "btrue", current_function);
  llvm::BasicBlock* else_block = nullptr;
  if (ctx->elsestmt != nullptr) {
    else_block = llvm::BasicBlock::Create(TheContext, "bfalse", current_function);
  }
  llvm::BasicBlock* rest_block = llvm::BasicBlock::Create(TheContext, "bend", current_function);
  if (else_block == nullptr) {
    else_block = rest_block;
  }
  Builder.CreateCondBr(
    std::any_cast<llvm::Value*>(ctx->ifexp->accept(this)),
    if_block,
    else_block
  );
  Builder.SetInsertPoint(if_block);
  ctx->ifstmt->accept(this);
  Builder.CreateBr(rest_block);
  if (ctx->elsestmt != nullptr) {
    Builder.SetInsertPoint(else_block);
    ctx->elsestmt->accept(this);
    Builder.CreateBr(rest_block);
  }
  Builder.SetInsertPoint(rest_block);
  return std::any();
}

std::any IRVisitor::visitNumberExpr(ExprParser::ExprContext *ctx) {
  return static_cast<llvm::Value*>(llvm::ConstantInt::get(Builder.getInt32Ty(), llvm::APInt(32, std::stoi(ctx->getText()), true)));
}

std::any IRVisitor::visitBraceExpr(ExprParser::ExprContext *ctx) {
  return ctx->exp->accept(this);
}

std::any IRVisitor::visitVarIdentExpr(ExprParser::ExprContext *ctx) {
  llvm::AllocaInst* alloca_inst = NamedVariables.at(ctx->variable_ident->getText());
  return static_cast<llvm::Value*>(Builder.CreateLoad(Builder.getInt32Ty(), alloca_inst));
}

std::any IRVisitor::visitAddExpr(ExprParser::ExprContext *ctx) {
  return Builder.CreateAdd(
    std::any_cast<llvm::Value*>(ctx->left->accept(this)),
    std::any_cast<llvm::Value*>(ctx->right->accept(this))
  );
}

std::any IRVisitor::visitSubExpr(ExprParser::ExprContext *ctx) {
  return Builder.CreateSub(
    std::any_cast<llvm::Value*>(ctx->left->accept(this)),
    std::any_cast<llvm::Value*>(ctx->right->accept(this))
  );
}

std::any IRVisitor::visitFunExpr(ExprParser::ExprContext *ctx) {
  string func_name = ctx->function_ident->getText();
  vector<llvm::Value*> arguments = std::any_cast<vector<llvm::Value*>>(ctx->arguments->accept(this));
  return Builder.CreateCall(NamedFunctions.at(func_name), arguments);
}

std::any IRVisitor::visitMoreExpr(ExprParser::ExprContext *ctx) {
  llvm::Value* lhs = std::any_cast<llvm::Value*>(ctx->left->accept(this));
  llvm::Value* rhs = std::any_cast<llvm::Value*>(ctx->right->accept(this));
  return Builder.CreateCmp(
    llvm::CmpInst::Predicate::ICMP_SGT,
    lhs,
    rhs
  );
}

std::any IRVisitor::visitLessExpr(ExprParser::ExprContext *ctx) {
  llvm::Value* lhs = std::any_cast<llvm::Value*>(ctx->left->accept(this));
  llvm::Value* rhs = std::any_cast<llvm::Value*>(ctx->right->accept(this));
  return Builder.CreateCmp(
    llvm::CmpInst::Predicate::ICMP_SLT,
    lhs,
    rhs
  );
}

std::any IRVisitor::visitEqualExpr(ExprParser::ExprContext *ctx) {
  llvm::Value* lhs = std::any_cast<llvm::Value*>(ctx->left->accept(this));
  llvm::Value* rhs = std::any_cast<llvm::Value*>(ctx->right->accept(this));
  return Builder.CreateCmp(
    llvm::CmpInst::Predicate::ICMP_EQ,
    lhs,
    rhs
  );
}

std::any IRVisitor::visitNotEqualExpr(ExprParser::ExprContext *ctx) {
  llvm::Value* lhs = std::any_cast<llvm::Value*>(ctx->left->accept(this));
  llvm::Value* rhs = std::any_cast<llvm::Value*>(ctx->right->accept(this));
  return Builder.CreateCmp(
    llvm::CmpInst::Predicate::ICMP_NE,
    lhs,
    rhs
  );
}

std::any IRVisitor::visitLessOrEqualExpr(ExprParser::ExprContext *ctx) {
  llvm::Value* lhs = std::any_cast<llvm::Value*>(ctx->left->accept(this));
  llvm::Value* rhs = std::any_cast<llvm::Value*>(ctx->right->accept(this));
  return Builder.CreateCmp(
    llvm::CmpInst::Predicate::ICMP_SLE,
    lhs,
    rhs
  );
}

std::any IRVisitor::visitMoreOrEqualExpr(ExprParser::ExprContext *ctx) {
  llvm::Value* lhs = std::any_cast<llvm::Value*>(ctx->left->accept(this));
  llvm::Value* rhs = std::any_cast<llvm::Value*>(ctx->right->accept(this));
  return Builder.CreateCmp(
    llvm::CmpInst::Predicate::ICMP_SGE,
    lhs,
    rhs
  );
}

std::any IRVisitor::visitMulExpr(ExprParser::ExprContext *ctx) {
  return Builder.CreateMul(
    std::any_cast<llvm::Value*>(ctx->left->accept(this)),
    std::any_cast<llvm::Value*>(ctx->right->accept(this))
  );
}

std::any IRVisitor::visitDivExpr(ExprParser::ExprContext *ctx) {
  return Builder.CreateUDiv(
    std::any_cast<llvm::Value*>(ctx->left->accept(this)),
    std::any_cast<llvm::Value*>(ctx->right->accept(this))
  );
}