#include <NFA.h>
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
    std::cout << nfa.GetStartState().ID() << ' ' << nfa.GetFinalStates().size()
              << std::endl;
    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}