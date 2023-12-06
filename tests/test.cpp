#include <State.h>
#include <Transition.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>

int main() {
  try {
    State state1;
    State state2;
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