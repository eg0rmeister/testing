#pragma once
#include <map>
#include <string>

#include "antlr4-runtime.h"
#include "libs/ExprBaseVisitor.h"

class InterpreterVisitor : ExprBaseVisitor {
 public:
  std::any visitFile(ExprParser::ProgContext *ctx);

  std::any visitProg(ExprParser::ProgContext *ctx);

  std::any visitExpr(ExprParser::ExprContext *ctx);

  std::any visitStmt(ExprParser::StmtContext *ctx);

 private:
  std::any visitPrintStmt(ExprParser::StmtContext *ctx);

  std::any visitAssignStmt(ExprParser::StmtContext *ctx);

  int visitNumberExpr(antlr4::Token* number);

  std::map<std::string, std::any> _variables;
};
