#include <FSA.h>
#include <State.h>
#include <Transition.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  std::string label1 = "awesome_label";
  std::string label2 = "another";
  std::string label3 = "label_to_add";
  auto type1 = COMMON;
  auto type2 = IDENT;
  try {
    State state1(label1, false, type1);
    State state2(label2, true, type2);

    std::vector<State> states;
    states.push_back(state1);
    states.push_back(state2);

    auto fsa = FSA(state1, states);
    auto state2_ptr = fsa.GetState(state2.ID());
    auto transition12 = Transition("a", state2_ptr);
    fsa.AddTransition(state1.ID(), transition12);
    fsa.SetFinal(state2.ID());
    assert((fsa.GetFinalStates().size() == 1));
    assert((fsa.GetFinalStates()[0] == state2));

    // Addittion test
    State state3(label3, true);
    fsa.AddState(state3, true);
    assert((fsa.GetFinalStates().size() == 2));

    // Duplication protection test
    fsa.AddState(state3, true);
    assert((fsa.GetFinalStates().size() == 2));

    // GetStates size test
    FSA::states_vec returned_states = fsa.GetStates();
    assert((returned_states.size() == 3));

    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}