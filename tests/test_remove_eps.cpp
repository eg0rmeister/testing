#include <REG_to_NFA.h>
#include <REGTree.h>
#include <NFA.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  try {

    nfa.Visualize();
    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}