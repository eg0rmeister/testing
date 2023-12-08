#include <DFA.h>
#include <DFA_Forest.h>
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
  std::string REG1 = "abc*";
  std::string REG2 = "ab*c";

  DFA dfa1 =
      ConvertNFAtoDFA(GetNFAWithNoEpsilons(GetNFAFromREG(REGTree(REG1))));
  DFA dfa2 =
      ConvertNFAtoDFA(GetNFAWithNoEpsilons(GetNFAFromREG(REGTree(REG2))));

  std::vector<DFA> dfa_vector;
  dfa_vector.push_back(dfa1);
  dfa_vector.push_back(dfa2);

  try {
    //
    // DFAForest test
    DFAForest forest(dfa_vector);
    
    // Beginning is not final test
    assert(!forest.IsFinal());

    //Movement test
    assert(!forest.Input("a"));
    assert(forest.Input("b"));
    assert(forest.IsFinal());
    assert(forest.Input("c"));

    // abc is accepted by both automatons
    assert(forest.WhichFinal().size() == 2);

    //abcc is accepted only by first automaton
    assert(forest.Input("c"));
    assert(forest.WhichFinal().size() == 1);
    assert(forest.WhichFinal()[0] == 0);
    
    //abccb is not accepted by any automatons
    assert(!forest.Input("b"));
    assert(forest.WhichFinal().size() == 0);

    forest.ResetState();

    assert(!forest.Input("a"));
    assert(forest.Input("b"));
    assert(!forest.Input("b"));

    // abbc is only accepted by second automaton
    assert(forest.Input("c"));
    assert(forest.IsFinal());
    assert(forest.WhichFinal().size() == 1);
    assert(forest.WhichFinal()[0] == 1);

  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
  }
}