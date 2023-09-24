#pragma once

#include <queue>
#include <string>
#include <vector>

class REGTree {
 public:
  enum OperationType {
    Concatenation,
    LetterConstant,
    Iteration,
    Addition,
    Backslash,
    Empty,
  };

 private:
  enum TokenType {
    LeftParenthesis,
    RightParenthesis,
    Letter,
    Iterate,
    Concatenate,
    Add,
  };

  struct Token {
    TokenType type;
    char letter = 0;
    Token(TokenType, char);
  };

  struct BaseNode {
    OperationType operation_type;
    char letter;
    std::vector<BaseNode*> children;
    BaseNode* parent = nullptr;
    BaseNode(const BaseNode&);
    BaseNode& operator=(const BaseNode&);
    ~BaseNode();
    BaseNode(char, BaseNode*);
    BaseNode(OperationType, BaseNode*);
  };

  bool IsLetter(char);

  BaseNode* root = nullptr;

  std::vector<Token> Tokenize(const std::string& REGexpr);
  std::queue<Token> ShuntingYard(const std::vector<Token>& tokens);
  static void swap(REGTree& left, REGTree& right);

 public:
  class Node {
    BaseNode* base = nullptr;
    Node(BaseNode*);

   public:
    Node(const REGTree&);
    Node GetLeftChild() const;
    Node GetRightChild() const;
    Node GetChild() const;
    OperationType GetType() const;
    char GetSymbol() const;
  };
  REGTree();
  REGTree(std::string);
  REGTree(const REGTree&);
  REGTree& operator=(const REGTree&);
  ~REGTree();
  Node GetRootNode();
};
