#include <DFA.h>
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
  std::string REG = "abc*";


  try {
    //
    // DFA tests
    DFA dfa =
        ConvertNFAtoDFA(GetNFAWithNoEpsilons(GetNFAFromREG(REGTree(REG))));
    
    // Beginning is neither final nor trash test
    assert(!dfa.IsFinal());
    assert(!dfa.IsInTrash());

    //Movement test
    assert(!dfa.Input("a"));
    assert(dfa.Input("b"));
    assert(dfa.IsFinal());
    assert(!dfa.IsInTrash());
    assert(dfa.Input("c"));

    //abcb leads dfa to trash
    assert(!dfa.Input("b"));
    assert(!dfa.IsFinal());
    assert(dfa.IsInTrash());
    
    //reset makes automaton go away from trash
    dfa.ResetState();
    assert(!dfa.IsInTrash());

    assert(!dfa.Input("a"));
    assert(dfa.Input("b"));
    assert(!dfa.IsInTrash());
    assert(!dfa.Input("b"));
    assert(dfa.IsInTrash());

  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
  }
}