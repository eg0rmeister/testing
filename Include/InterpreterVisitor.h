#pragma once
#include <map>
#include <string>

#include "antlr4-runtime.h"
#include "ExprBaseVisitor.h"

#include "StackMemory.h"
#include "Printable.h"

class InterpreterVisitor : ExprBaseVisitor {
 public:
  std::any visitFile(ExprParser::FileContext *context) override;

  std::any visitProg(ExprParser::ProgContext *ctx) override;

  std::any visitExpr(ExprParser::ExprContext *ctx) override;

  std::any visitStmt(ExprParser::StmtContext *ctx) override;

  std::any visitFun(ExprParser::FunContext *context) override;

  std::any visitIdents(ExprParser::IdentsContext *context) override;

  std::any visitExprs(ExprParser::ExprsContext *context) override;

  std::any visitStatements(ExprParser::StatementsContext *context) override;

 private:

  std::any visitPrintStmt(ExprParser::StmtContext *ctx);

  std::any visitAssignStmt(ExprParser::StmtContext *ctx);

  std::any visitExecuteStmt(ExprParser::StmtContext *ctx);

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
  std::map<std::string, ExprParser::FunContext*> _functions;
};
