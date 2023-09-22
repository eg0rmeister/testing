#include <State.h>

#include <iostream>
#include <string>
#include <cassert>
#include <unordered_set>

int main() {
  std::string label1 = "awesome_label";
  std::string label2 = "another";
  auto type1 = COMMON;
  auto type2 = IDENT;
  try {
    State state1(label1, false, type1);
    State state2(label2, true, type2);
    assert((state1.Label() == label1));
    assert((state2.Label() == label2));
    assert((state1.Type() == type1));
    assert((state2.Type() == type2));
    assert((state1.ID() == 1));
    assert((state2.ID() == 2));
    std::unordered_set<State> states;
    states.insert(state1);
    std::cout << "OK" << '\n';
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
  }
}