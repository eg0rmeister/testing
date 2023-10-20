#include <iostream>
#include "antlr4-runtime.h"
#include "libs/ExprLexer.h"
#include "libs/ExprParser.h"
#include "NewExprVisitor.h"

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open("input.txt");
    
    antlr4::ANTLRInputStream input(stream);
    ExprLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ExprParser parser(&tokens);    
    
    ExprParser::ProgContext* tree = parser.prog();

    NewExprVisitor visitor;
    auto ast_tree = visitor.visitFile(tree);

    return 0;
}