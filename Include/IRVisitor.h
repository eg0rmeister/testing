#pragma once
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "ExprBaseVisitor.h"
#include "Printable.h"
#include "StackMemory.h"
#include "antlr4-runtime.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

class IRVisitor : ExprBaseVisitor {
 public:
  IRVisitor() : Builder(TheContext), TheModule("test", TheContext) {}

  std::any visitFile(ExprParser::FileContext *context) override;

  std::any visitProg(ExprParser::ProgContext *ctx) override;

  std::any visitExpr(ExprParser::ExprContext *ctx) override;

  std::any visitStmt(ExprParser::StmtContext *ctx) override;

  std::any visitFun(ExprParser::FunContext *context) override;

  std::any visitIdents(ExprParser::IdentsContext *context) override;

  std::any visitExprs(ExprParser::ExprsContext *context) override;

  void printIR();

  void printIR(std::string filename);

 private:

  std::any visitPrintStmt(ExprParser::StmtContext *ctx);

  std::any visitAssignStmt(ExprParser::StmtContext *ctx);

  std::any visitExecuteStmt(ExprParser::StmtContext *ctx);

  std::any visitDeclareStmt(ExprParser::StmtContext *ctx);

  std::any visitIfStmt(ExprParser::StmtContext *ctx); 

  std::any visitWhileStmt(ExprParser::StmtContext *ctx);

  std::any visitNumberExpr(ExprParser::ExprContext *ctx);

  std::any visitBraceExpr(ExprParser::ExprContext *ctx);

  std::any visitVarIdentExpr(ExprParser::ExprContext *ctx);

  std::any visitDivExpr(ExprParser::ExprContext *ctx);

  std::any visitMulExpr(ExprParser::ExprContext *ctx);

  std::any visitAddExpr(ExprParser::ExprContext *ctx);

  std::any visitSubExpr(ExprParser::ExprContext *ctx);

  std::any visitFunExpr(ExprParser::ExprContext *ctx);

  std::any visitMoreExpr(ExprParser::ExprContext *ctx);

  std::any visitLessExpr(ExprParser::ExprContext *ctx);

  std::any visitEqualExpr(ExprParser::ExprContext *ctx);

  std::any visitNotEqualExpr(ExprParser::ExprContext *ctx);

  std::any visitLessOrEqualExpr(ExprParser::ExprContext *ctx);

  std::any visitMoreOrEqualExpr(ExprParser::ExprContext *ctx);

  StackMemory memory;

  llvm::LLVMContext TheContext;
  llvm::IRBuilder<> Builder;
  llvm::Module TheModule;
  std::map<std::string, llvm::Value *> NamedValues;
  std::map<std::string, llvm::Function *> NamedFunctions;
  std::map<std::string, llvm::AllocaInst *> NamedVariables;
  llvm::Function* current_function;
};
