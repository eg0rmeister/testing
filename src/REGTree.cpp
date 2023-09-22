#ifndef REGTREE_CPP
#define REGTREE_CPP

#include "../include/REGTree.hpp"

#include <iostream>
#include <queue>
#include <stack>

REGTree::Token::Token(TokenType type, char letter = 0)
    : type(type), letter(letter){};

REGTree::Node::Node(char letter, Node* parent)
    : operation_type(LetterConstant), letter(letter) {}

REGTree::Node::Node(typename REGTree::OperationType operation_type,
                    Node* parent)
    : operation_type(operation_type) {}

REGTree::Node::~Node() {
  for (auto node : children) {
    delete node;
  }
}

REGTree::~REGTree() { delete root; }

bool REGTree::IsLetter(char letter) {
  return (letter >= '0' && letter <= '9') || (letter >= 'a' && letter <= 'z') ||
         (letter >= 'A' && letter <= 'Z');
}

std::vector<typename REGTree::Token> REGTree::Tokenize(const std::string& str) {
  std::vector<Token> ret = std::vector<Token>();
  ret.reserve(str.length());
  for (size_t i = 0; i < str.length(); ++i) {
    if (IsLetter(str[i])) {
      ret.push_back(Token(Letter, str[i]));
      if (((i + 1) < str.size()) && IsLetter(str[i + 1]) || str[i + 1] == '(') {
        ret.push_back(Token(Concatenate));
      }
    }
    if (str[i] == '(') {
      ret.push_back(Token(LeftParenthesis));
    }
    if (str[i] == ')') {
      ret.push_back(Token(RightParenthesis));
      if (((i + 1) < str.size()) && IsLetter(str[i + 1]) || str[i + 1] == '(') {
        ret.push_back(Token(Concatenate));
      }
    }
    if (str[i] == '+') {
      ret.push_back(Token(Add));
    }
    if (str[i] == '*') {
      ret.push_back(Token(Iterate));
      if (((i + 1) < str.size()) && IsLetter(str[i + 1]) || str[i + 1] == '(') {
        ret.push_back(Token(Concatenate));
      }
    }
  }
  return ret;
}

std::vector<typename REGTree::Token> REGTree::ShuntingYard(
    const std::vector<Token>& tokens) {
  std::vector<Token> ret;
  std::stack<Token> operators;
  size_t i;
  for (i = 0; i < tokens.size(); ++i) {
    if (tokens[i].type == Letter) {
      ret.push_back(tokens[i]);
      continue;
    }
    if (tokens[i].type == Iterate) {
      while (!operators.empty() && operators.top().type == Iterate) {
        ret.push_back(operators.top());
        operators.pop();
      }
      operators.push(tokens[i]);
      continue;
    }
    if (tokens[i].type == Concatenate) {
      while (!operators.empty() && (operators.top().type == Iterate ||
                                    operators.top().type == Concatenate)) {
        ret.push_back(operators.top());
        operators.pop();
      }
      operators.push(tokens[i]);
      continue;
    }
    if (tokens[i].type == Add) {
      while (!operators.empty() && (operators.top().type == Iterate ||
                                    operators.top().type == Concatenate ||
                                    operators.top().type == Add)) {
        ret.push_back(operators.top());
        operators.pop();
      }
      operators.push(tokens[i]);
      continue;
    }
    if (tokens[i].type == LeftParenthesis) {
      operators.push(tokens[i]);
      continue;
    }
    if (tokens[i].type == RightParenthesis) {
      while (operators.top().type != LeftParenthesis) {
        ret.push_back(operators.top());
        operators.pop();
      }
      operators.pop();
      continue;
    }
  }
  while (!operators.empty()) {
    ret.push_back(operators.top());
    operators.pop();
  }
  return ret;
}

REGTree::REGTree(std::string regexp_string) {
  std::vector<Token> regexp = ShuntingYard(Tokenize(regexp_string));
}

#endif