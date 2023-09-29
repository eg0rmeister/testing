#include <NFA.h>
#include <State.h>
#include <Transition.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  std::string label1 = "left_start";
  std::string label2 = "left_end";
  std::string label3 = "right_start";
  std::string label4 = "right_middle";
  std::string label5 = "right_end";

  try {
    State state1(label1, false);
    State state2(label2, true);
    State state3(label3, false);
    State state4(label4, false);
    State state5(label5, true);

    std::vector<State> left_states;
    left_states.push_back(state1);
    left_states.push_back(state2);

    std::vector<State> right_states;
    right_states.push_back(state3);
    right_states.push_back(state4);
    right_states.push_back(state5);

    NFA left_nfa(state1, left_states);
    NFA right_nfa(state3, right_states);

    auto state2_ptr = left_nfa.GetState(state2.ID());
    auto state3_ptr = left_nfa.GetState(state3.ID());
    auto state4_ptr = left_nfa.GetState(state4.ID());
    auto state5_ptr = left_nfa.GetState(state5.ID());
    auto transition12 = Transition("a", state2_ptr);
    auto transition34 = Transition("b", state4_ptr);
    auto transition35 = Transition("c", state5_ptr);
    auto transition45 = Transition("d", state5_ptr);
    auto transition43 = Transition("e", state5_ptr);
    left_nfa.AddTransition(state1.ID(), transition12);
    right_nfa.AddTransition(state3.ID(), transition34);
    right_nfa.AddTransition(state3.ID(), transition35);
    right_nfa.AddTransition(state4.ID(), transition45);
    right_nfa.AddTransition(state4.ID(), transition43);

    left_nfa.SetFinal(state2.ID());
    right_nfa.SetFinal(state5.ID());

    // Test Concatenation
    NFA concatenated = ConcatenateNFA(left_nfa, right_nfa);

    // Test transitions amount
    assert(concatenated.GetAllTransitions().size() == 6);

    // Test state amount
    assert(concatenated.GetStates().size() == 5);

    // Test final states amount
    assert(concatenated.GetFinalStates().size() == 1);

    // Test epsilon transition
    assert(concatenated.GetAllTransitions()[state2.ID()][0].Input() == "");

    //
    // Test Iteration
    NFA iterated = IterateNFA(right_nfa);

    // Test transitions amount
    assert(iterated.GetAllTransitions().size() == 6);

    // Test state amount
    assert(iterated.GetStates().size() == 4);

    // Test final states amount
    assert(iterated.GetFinalStates().size() == 1);

    // Test final state
    assert(iterated.GetFinalStates()[0].ID() == iterated.GetStartState().ID());

    // Test epsilon transitions
    assert(iterated.GetAllTransitions()[state5.ID()][0].Input() == "");
    assert(iterated.GetAllTransitions()[iterated.GetStartState().ID()][0]
               .Input() == "");

    //
    // Test Addition
    NFA added = AddNFA(left_nfa, right_nfa);

    // Test transitions amount
    assert(added.GetAllTransitions().size() == 9);

    // Test state amount
    assert(added.GetStates().size() == 7);

    // Test final states amount
    assert(added.GetFinalStates().size() == 1);

    // Test epsilon transition
    assert(added.GetAllTransitions()[state2.ID()][0].Input() == "");
    assert(added.GetAllTransitions()[state5.ID()][0].Input() == "");
    assert(added.GetAllTransitions()[added.GetStartState().ID()][0].Input() == "");
    assert(added.GetAllTransitions()[added.GetStartState().ID()][1].Input() == "");

    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}