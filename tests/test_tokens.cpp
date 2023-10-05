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
  std::string REG0 = "int";
  std::string REG1 = "aa*bb*";

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
    std::vector<size_t>tokens = {TYPE, VAR};
    Scanner scanner(dfa_forest, tokens);

    // Scanner input
    std::string line_of_code = "int abb;";
    std::string result = "";
    for (size_t i = 0; i < line_of_code.length(); ++i) {
      if (scanner.Input(std::string(1, line_of_code[i]))) {
        result += scanner.GetLastToken().Type();
        result += ' ';
        scanner.Reset();
      }
    }
    std::cout << result << '\n';
    assert((result == "TYPE VAR "));

  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
  }
}