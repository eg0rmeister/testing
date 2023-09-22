#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "string"
#include "vector"

class REGTree {
  enum OperationType {
    Concatenation,
    Addition,
    LetterConstant,
    Iteration,
    Backslash,
    Parenthesis,
    Empty
  };

  enum TokenType {
    LeftParenthesis,
    RightParenthesis,
    Concatenate,
    Add,
    Iterate,
    Letter
  };

  struct Token {
    TokenType type;
    char letter = 0;
    Token(TokenType, char);
  };

  struct Node {
    OperationType operation_type;
    char letter;
    std::vector<Node*> children;
    Node* parent = nullptr;
    ~Node();
    Node(char, Node*);
    Node(OperationType, Node*);
  };

  bool IsLetter(char);

  Node* root = nullptr;

  std::vector<Token> Tokenize(const std::string& REGexpr);
  std::queue<Token> ShuntingYard(const std::vector<Token>& tokens);

 public:
  REGTree(std::string);
  ~REGTree();
};

#endif