#pragma once
#include <string>

#include "antlr4-runtime.h"
#include "libs/ExprBaseVisitor.h"

class NewExprVisitor : ExprBaseVisitor {
 public:
  std::any visitFile(ExprParser::ProgContext *ctx);
};