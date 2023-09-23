#include <FSA.h>
#include <NFA.h>
#include <State.h>
#include <Transition.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  try {
    auto nfa1 = BuildEpsNFA();
    auto nfa2 = BuildOneLetterNFA("b");
    
    std::cout << "=NFA#1(eps)=\n";
    nfa1.Visualize();
    std::cout << "\n=NFA#2(let)=\n";
    nfa2.Visualize();

  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
  }
}