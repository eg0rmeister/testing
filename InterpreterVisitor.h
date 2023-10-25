#pragma once
#include <map>
#include <string>

#include "antlr4-runtime.h"
#include "libs/ExprBaseVisitor.h"

struct Printable {
  Printable();
  Printable(std::any value, std::string str);
  std::any value;
  std::string str;
};

class InterpreterVisitor : ExprBaseVisitor {
 public:
  std::any visitFile(ExprParser::ProgContext *ctx);

  std::any visitProg(ExprParser::ProgContext *ctx);

  std::any visitExpr(ExprParser::ExprContext *ctx);

  std::any visitStmt(ExprParser::StmtContext *ctx);

 private:
  /// @brief Wrapper around std::any to print variables of any type

  std::any visitPrintStmt(ExprParser::StmtContext *ctx);

  std::any visitAssignStmt(ExprParser::StmtContext *ctx);

  std::any visitNumberExpr(ExprParser::ExprContext *ctx);

  std::any visitBraceExpr(ExprParser::ExprContext *ctx);

  std::any visitIdentExpr(ExprParser::ExprContext *ctx);

  std::any visitDivExpr(ExprParser::ExprContext *ctx);

  std::any visitMulExpr(ExprParser::ExprContext *ctx);

  std::any visitAddExpr(ExprParser::ExprContext *ctx);

  std::any visitSubExpr(ExprParser::ExprContext *ctx);

  std::map<std::string, Printable> _variables;
};
