#include <iostream>

#include "InterpreterVisitor.h"
#include "NewExprVisitor.h"
#include "antlr4-runtime.h"
#include "libs/ExprLexer.h"
#include "libs/ExprParser.h"

int main(int argc, const char* argv[]) {
  std::ifstream stream;
  stream.open("input.txt");

  antlr4::ANTLRInputStream input(stream);
  ExprLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  ExprParser parser(&tokens);

  ExprParser::ProgContext* tree = parser.prog();

  InterpreterVisitor visitor;
  try {
    visitor.visitProg(tree);
  } catch (...) {
    std::cout << "Error occured!\n";
  }

  return 0;
}