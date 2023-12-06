#include <NFA.h>
#include <State.h>
#include <Transition.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  State state0;
  State state1;
  State state2;
  State state3;
  State state4;
  State state5;
  std::vector<State> states;
  states.push_back(state0);
  states.push_back(state1);
  states.push_back(state2);
  states.push_back(state3);
  states.push_back(state4);
  states.push_back(state5);

  Transition transition01 = Transition("a", state1);
  Transition transition03 = Transition("~", state3);
  Transition transition13 = Transition("c", state3);
  Transition transition21 = Transition("b", state1);
  Transition transition32 = Transition("~", state2);
  Transition transition34 = Transition("~", state4);
  Transition transition45 = Transition("~", state5);
  Transition transition52 = Transition("c", state2);

  NFA nfa_with_eps(state0, states);
  nfa_with_eps.AddTransition(state0.ID(), transition01);
  nfa_with_eps.AddTransition(state0.ID(), transition03);
  nfa_with_eps.AddTransition(state1.ID(), transition13);
  nfa_with_eps.AddTransition(state2.ID(), transition21);
  nfa_with_eps.AddTransition(state3.ID(), transition32);
  nfa_with_eps.AddTransition(state3.ID(), transition34);
  nfa_with_eps.AddTransition(state4.ID(), transition45);
  nfa_with_eps.AddTransition(state5.ID(), transition52);

  nfa_with_eps.SetFinal(state5.ID());
  

  try {
    //
    // Test Epsilon removal
    NFA nfa_without_eps = GetNFAWithNoEpsilons(nfa_with_eps);
    nfa_without_eps.Visualize();
    // Test state amount
    assert(nfa_without_eps.GetStates().size() == 4);

    // Test final states amount
    assert(nfa_without_eps.GetFinalStates().size() == 2);

    return 0;
  } catch (const std::exception& e) {
    std::cout << "FAILED with error " << ' ' << e.what() << '\n';
    return 1;
  }
}