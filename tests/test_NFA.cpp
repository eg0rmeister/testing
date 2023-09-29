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
    State state1(label1, type1);
    State state2(label2, type2);

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
    State state3(label3);
    fsa.AddState(state3, true);
    assert((fsa.GetFinalStates().size() == 2));

    // Duplication protection test
    fsa.AddState(state3, true);
    assert((fsa.GetFinalStates().size() == 2));

    // GetStates size test
    FSA::states_vec returned_states = fsa.GetStates();
    assert((returned_states.size() == 3));

    // GetStartState test
    State start_state = fsa.GetStartState();
    assert((start_state.ID() == state1.ID()));

    // GetAllTransitions test
    FSA::transitions_map transitions = fsa.GetAllTransitions();
    assert((transitions.size() == 1));
    assert((transitions[state1.ID()].size() == 1));
    assert((transitions[state1.ID()][0].Target()->ID() == state2.ID()));

    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}