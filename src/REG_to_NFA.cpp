#include <REG_to_NFA.h>

NFA GetNFAFromNode(const REGTree::Node node) {
  switch (node.GetType()) {
    case REGTree::Concatenation:
      return ConcatenateNFA(GetNFAFromNode(node.GetLeftChild()),
                            GetNFAFromNode(node.GetRightChild()));
      break;

    case REGTree::LetterConstant:
      return BuildOneLetterNFA(std::string(node.GetSymbol(), 1));
      break;

    case REGTree::Iteration:
      return IterateNFA(GetNFAFromNode(node.GetLeftChild()));
      break;

    case REGTree::Addition:
      return AddNFA(GetNFAFromNode(node.GetLeftChild()),
                    GetNFAFromNode(node.GetRightChild()));
      break;

    default:
      throw std::runtime_error("REGTree is invalid");
  }
}

NFA GetNFAFromREG(const REGTree tree) {
  return GetNFAFromNode(tree.GetRootNode());
}
