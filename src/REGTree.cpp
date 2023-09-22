#ifndef REGTREE_CPP
#define REGTREE_CPP

#include "REGTree.hpp"

#include <iostream>
#include <queue>
#include <stack>

#include "REGTree.hpp"

REGTree::Token::Token(TokenType type, char letter = 0)
    : type(type), letter(letter){};

REGTree::BaseNode::BaseNode(char letter, BaseNode* parent)
    : operation_type(LetterConstant), letter(letter) {}

REGTree::BaseNode::BaseNode(typename REGTree::OperationType operation_type,
                            BaseNode* parent)
    : operation_type(operation_type) {}

REGTree::BaseNode::BaseNode(const BaseNode& other)
    : operation_type(other.operation_type), letter(other.letter) {
  children.reserve(other.children.size());
  for (const BaseNode* node : other.children) {
    children.push_back(new BaseNode(*node));
  }
  if (other.parent == nullptr) {
    parent = nullptr;
  } else {
    parent = new BaseNode(*other.parent);
  }
}

typename REGTree::BaseNode& REGTree::BaseNode::operator=(
    const BaseNode& other) {
  if (this == &other) {
    return *this;
  }
  BaseNode copied_node(other);
  std::swap(*this, copied_node);
  return *this;
}

REGTree::BaseNode::~BaseNode() {
  for (BaseNode* node : children) {
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

std::queue<typename REGTree::Token> REGTree::ShuntingYard(
    const std::vector<Token>& tokens) {
  std::queue<Token> ret;
  std::stack<Token> operators;
  size_t i;
  for (i = 0; i < tokens.size(); ++i) {
    if (tokens[i].type == Letter) {
      ret.push(tokens[i]);
      continue;
    }
    if (tokens[i].type == Iterate) {
      while (!operators.empty() && operators.top().type == Iterate) {
        ret.push(operators.top());
        operators.pop();
      }
      operators.push(tokens[i]);
      continue;
    }
    if (tokens[i].type == Concatenate) {
      while (!operators.empty() && (operators.top().type == Iterate ||
                                    operators.top().type == Concatenate)) {
        ret.push(operators.top());
        operators.pop();
      }
      operators.push(tokens[i]);
      continue;
    }
    if (tokens[i].type == Add) {
      while (!operators.empty() && (operators.top().type == Iterate ||
                                    operators.top().type == Concatenate ||
                                    operators.top().type == Add)) {
        ret.push(operators.top());
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
        ret.push(operators.top());
        operators.pop();
      }
      operators.pop();
      continue;
    }
  }
  while (!operators.empty()) {
    ret.push(operators.top());
    operators.pop();
  }
  return ret;
}

REGTree::REGTree(std::string regexp_string) {
  std::queue<Token> regexp = ShuntingYard(Tokenize(regexp_string));

  std::stack<BaseNode*> nodes;
  while (!regexp.empty()) {
    Token token = regexp.front();
    regexp.pop();
    if (token.type == Letter) {
      nodes.push(new BaseNode(token.letter, nullptr));
    }
    if (token.type == Iterate) {
      BaseNode* child = nodes.top();
      nodes.pop();
      nodes.push(new BaseNode(Iteration, nullptr));
      nodes.top()->children.push_back(child);
      child->parent = nodes.top();
    }
    if (token.type == Concatenate) {
      BaseNode* right_child = nodes.top();
      nodes.pop();
      BaseNode* left_child = nodes.top();
      nodes.pop();
      nodes.push(new BaseNode(Concatenation, nullptr));
      left_child->parent = nodes.top();
      right_child->parent = nodes.top();
      nodes.top()->children.push_back(left_child);
      nodes.top()->children.push_back(right_child);
    }
    if (token.type == Add) {
      BaseNode* right_child = nodes.top();
      nodes.pop();
      BaseNode* left_child = nodes.top();
      nodes.pop();
      nodes.push(new BaseNode(Addition, nullptr));
      left_child->parent = nodes.top();
      right_child->parent = nodes.top();
      nodes.top()->children.push_back(left_child);
      nodes.top()->children.push_back(right_child);
    }
  }
  root = nodes.top();
}

REGTree::REGTree(const REGTree& other) { root = new BaseNode(*other.root); }

REGTree& REGTree::operator=(const REGTree& other) {
  if (this == &other) {
    return *this;
  }
  REGTree copy(other);
  std::swap(*this, copy);
  return *this;
}

REGTree::Node::Node(BaseNode* base) : base(base) {}

REGTree::Node::Node(const REGTree& tree) : base(tree.root) {}

typename REGTree::Node REGTree::Node::GetLeftChild() { return GetChild(); }

typename REGTree::Node REGTree::Node::GetRightChild() {
  return Node(base->children[1]);
}

typename REGTree::Node REGTree::Node::GetChild() {
  return Node(base->children[0]);
}

typename REGTree::OperationType REGTree::Node::GetType() {
  return base->operation_type;
}

char REGTree::Node::GetSymbol() { return base->letter; }

#endif