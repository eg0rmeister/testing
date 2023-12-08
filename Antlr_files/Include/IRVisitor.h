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

 private:
  std::any visitPrintStmt(ExprParser::StmtContext *ctx);

  std::any visitAssignStmt(ExprParser::StmtContext *ctx);

  std::any visitExecuteStmt(ExprParser::StmtContext *ctx);

  std::any visitNumberExpr(ExprParser::ExprContext *ctx);

  std::any visitBraceExpr(ExprParser::ExprContext *ctx);

  std::any visitVarIdentExpr(ExprParser::ExprContext *ctx);

  std::any visitDivExpr(ExprParser::ExprContext *ctx);

  std::any visitMulExpr(ExprParser::ExprContext *ctx);

  std::any visitAddExpr(ExprParser::ExprContext *ctx);

  std::any visitSubExpr(ExprParser::ExprContext *ctx);

  std::any visitFunExpr(ExprParser::ExprContext *ctx);

  StackMemory memory;
  std::map<std::string, ExprParser::FunContext *> _functions;

  llvm::LLVMContext TheContext;
  llvm::IRBuilder<> Builder;
  llvm::Module TheModule;
  std::map<std::string, llvm::Value *> NamedValues;
};
