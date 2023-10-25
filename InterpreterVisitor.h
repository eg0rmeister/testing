#pragma once
#include <string>

#include "antlr4-runtime.h"
#include "libs/ExprBaseVisitor.h"

class InterpreterVisitor : ExprBaseVisitor {
 public:
  std::any visitFile(ExprParser::ProgContext *ctx);

  std::any visitProg(ExprParser::ProgContext *ctx);

  std::any visitExpr(ExprParser::ExprContext *ctx);

  std::any visitStmt(ExprParser::StmtContext *ctx);
};
