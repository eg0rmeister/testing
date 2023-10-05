#include "DFA.h"
#include "DFA_Forest.h"
#include "NFA.h"
#include "NFA_to_DFA.h"
#include "REGTree.h"
#include "REG_to_NFA.h"
#include "Scanner.h"

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  std::string REG1 = "abc*";
  std::string REG2 = "ab*c";

  DFA dfa1 =
      ConvertNFAtoDFA(GetNFAWithNoEpsilons(GetNFAFromREG(REGTree(REG1))));
  DFA dfa2 =
      ConvertNFAtoDFA(GetNFAWithNoEpsilons(GetNFAFromREG(REGTree(REG2))));

  std::vector<DFA> dfa_vector;
  dfa_vector.push_back(dfa1);
  dfa_vector.push_back(dfa2);
  DFAForest dfa_forest(dfa_vector);
  try {
    //
    // Scanner test
    Scanner scanner(dfa_forest);

    // Scanner input
    assert(!scanner.Input("a"));
    assert(!scanner.Input("b"));
    assert(!scanner.Input("b"));
    assert(!scanner.Input("b"));
    assert(!scanner.Input("c"));
    assert(scanner.Input(" "));
    assert(scanner.Input("b"));

    // Scanner reset and input
    scanner.Reset();
    assert(!scanner.Input("a"));
    assert(!scanner.Input("b"));
    assert(!scanner.Input("b"));
    assert(!scanner.Input("b"));
    assert(!scanner.Input("c"));
    assert(scanner.Input(" "));
    assert(scanner.Input("b"));

  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
  }
}