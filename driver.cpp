#include <iostream>

#include "InterpreterVisitor.h"
#include "PrintVisitor.h"
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"

int main(int argc, const char* argv[]) {
  std::ifstream stream;
  stream.open("../input.txt");

  antlr4::ANTLRInputStream input(stream);
  ExprLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  ExprParser parser(&tokens);

  ExprParser::FileContext* tree = parser.file();

  InterpreterVisitor visitor;
  PrintVisitor print_visitor;
  try {
    print_visitor.visitFile(tree);
  } catch (const std::exception& ex) {
    std::cout << "Error occured!\n" << ex.what() << std::endl;
  }
  try {
    visitor.visitFile(tree);
  } catch (const std::exception& ex) {
    std::cout << "Error occured!\n" << ex.what() << std::endl;
  }

  return 0;
}