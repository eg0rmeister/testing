#include <iostream>

#include "InterpreterVisitor.h"
#include "NewExprVisitor.h"
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"

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
  } catch (const std::exception& ex) {
    std::cout << "Error occured!\n" << ex.what();
  }

  return 0;
}