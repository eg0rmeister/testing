#include <State.h>
#include <Transition.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>

int main() {
  std::string label1 = "awesome_label";
  std::string label2 = "another";
  auto type1 = COMMON;
  auto type2 = IDENT;
  try {
    State state1(label1, type1);
    State state2(label2, type2);
    assert((state1.Label() == label1));
    assert((state2.Label() == label2));
    assert((state1.Type() == type1));
    assert((state2.Type() == type2));
    assert((state1.ID() == 0));
    assert((state2.ID() == 1));
    std::unordered_set<State> states;
    states.insert(state1);
    std::cout << "OK" << '\n';

    State state1_copy(state1);
    State* state1_copy_ptr(new State(state1));
    assert((state1.ID() == state1_copy.ID()));
    assert((state1.ID() == state1_copy_ptr->ID()));
    delete state1_copy_ptr;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
  }
}