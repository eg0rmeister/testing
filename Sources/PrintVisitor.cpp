#include <string>
#include <iostream>
#include "PrintVisitor.h"

std::any PrintVisitor::visitFile(ExprParser::FileContext* context) {
  std::cout << "File: " << context->getText() << std::endl;
  for (auto function : context->fun()) {
    function->accept(this);
  }
  context->prog()->accept(this);
  return std::any();
}
