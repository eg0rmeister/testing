#include <NFA.h>
#include <NFA_to_DFA.h>
#include <REGTree.h>
#include <REG_to_NFA.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  std::string regexp = "ab*+c";
  try {
    REGTree regtree(regexp);
    NFA nfa = GetNFAFromREG(regtree);
    nfa.Visualize();
    nfa = GetNFAWithNoEpsilons(nfa);
    nfa.Visualize();
    auto dfa = ConvertNFAtoDFA(nfa);
    dfa.Visualize();
    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}