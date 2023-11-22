#include <string>
#include <iostream>
#include "PrintVisitor.h"

std::any PrintVisitor::visitFile(ExprParser::FileContext* context) {
  std::cout << "File" << std::endl;
  for (auto function : context->fun()) {
    function->accept(this);
  }
  context->prog()->accept(this);
  return std::any();
}

std::any PrintVisitor::visitProg(ExprParser::ProgContext* ctx) {
  std::cout << "Main" << std::endl;
  for (auto statement : ctx->stmt()) {
    statement->accept(this);
  }
  return std::any();
}
