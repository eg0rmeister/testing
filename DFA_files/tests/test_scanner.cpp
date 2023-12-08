#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "DFA.h"
#include "DFA_Forest.h"
#include "NFA.h"
#include "NFA_to_DFA.h"
#include "REGTree.h"
#include "REG_to_NFA.h"
#include "Scanner.h"

int main() {
  std::string REG0 = "abc*";
  std::string REG1 = "ab*c";

  DFA dfa0 =
      ConvertNFAtoDFA(GetNFAWithNoEpsilons(GetNFAFromREG(REGTree(REG0))));
  DFA dfa1 =
      ConvertNFAtoDFA(GetNFAWithNoEpsilons(GetNFAFromREG(REGTree(REG1))));

  std::vector<DFA> dfa_vector;
  dfa_vector.push_back(dfa0);
  dfa_vector.push_back(dfa1);
  DFAForest dfa_forest(dfa_vector);
  try {
    //
    // Scanner test
    Scanner scanner(dfa_forest);

    // Scanner input
    assert(!scanner.Input("a"));
    assert(!scanner.Input("b"));

    assert(scanner.GetCurrentString() == "ab");
    assert(scanner.GetLastTerminalString() == "ab");
    assert(scanner.GetLastTerminalId() == 0);

    assert(!scanner.Input("b"));
    assert(!scanner.Input("b"));
    assert(!scanner.Input("c"));
    assert(scanner.Input(" "));
    assert(scanner.Input("b"));
    assert(scanner.GetCurrentString() == "abbbc b");
    assert(scanner.GetLastTerminalString() == "abbbc");
    assert(scanner.GetLastTerminalId() == 1);

    // Scanner reset and input
    scanner.Reset();
    assert(!scanner.Input("a"));
    assert(!scanner.Input("b"));

    assert(scanner.GetCurrentString() == "ab");
    assert(scanner.GetLastTerminalString() == "ab");
    assert(scanner.GetLastTerminalId() == 0);
    
    assert(!scanner.Input("b"));
    assert(!scanner.Input("b"));
    assert(!scanner.Input("c"));
    assert(scanner.Input(" "));
    assert(scanner.Input("b"));
    assert(scanner.GetCurrentString() == "abbbc b");
    assert(scanner.GetLastTerminalString() == "abbbc");
    assert(scanner.GetLastTerminalId() == 1);

  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
  }
}