#include <cassert>
#include <iostream>
#include <string>

#include "REGTree.h"

std::string PrintRegexBasedOnTree(const REGTree::Node& node) {
  if (node.GetType() == REGTree::LetterConstant) {
    return std::string(1, node.GetSymbol());
  }
  if (node.GetType() == REGTree::Iteration) {
    return '(' + PrintRegexBasedOnTree(node.GetChild()) + '*' + ')';
  }
  if (node.GetType() == REGTree::Concatenation) {
    return '(' + PrintRegexBasedOnTree(node.GetLeftChild()) + '.' +
           PrintRegexBasedOnTree(node.GetRightChild()) + ')';
  }
  if (node.GetType() == REGTree::Addition) {
    return '(' + PrintRegexBasedOnTree(node.GetLeftChild()) + '+' +
           PrintRegexBasedOnTree(node.GetRightChild()) + ')';
  }
  if (node.GetType() == REGTree::Empty) {
    return "";
  }
  return "^WTF^";
}

int main() {
  try {
    // Creating and copying an empty tree
    REGTree empty_tree;
    REGTree copycat(empty_tree);
    assert(PrintRegexBasedOnTree(empty_tree) == PrintRegexBasedOnTree(copycat));
    assert(PrintRegexBasedOnTree(empty_tree) == "");

    // Creating and assigning a tree
    std::string regexpr = "(he)*+(g)";
    REGTree greeting_tree(regexpr);
    std::cerr << PrintRegexBasedOnTree(greeting_tree) << std::endl;
    copycat = greeting_tree;
    assert(PrintRegexBasedOnTree(greeting_tree) ==
           PrintRegexBasedOnTree(copycat));
    assert(PrintRegexBasedOnTree(greeting_tree) == "(((h.e)*)+g)");

    // Check that the types and the traversing are correct
    REGTree::Node root = greeting_tree.GetRootNode();
    assert(root.GetLeftChild().GetChild().GetLeftChild().GetType() ==
           REGTree::LetterConstant);
    assert(root.GetLeftChild().GetChild().GetRightChild().GetType() ==
           REGTree::LetterConstant);
    assert(root.GetLeftChild().GetChild().GetType() == REGTree::Concatenation);
    assert(root.GetLeftChild().GetType() == REGTree::Iteration);

    assert(root.GetRightChild().GetType() == REGTree::LetterConstant);
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}