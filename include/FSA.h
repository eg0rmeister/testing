// Finite-State Automaton

#ifndef COMPILER_FSA_H
#define COMPILER_FSA_H

#include <State.h>
#include <Transition.h>

#include <unordered_map>
#include <unordered_set>

class FSA {
 public:
  using states_set = std::unordered_set<State>;
  using transitions_set = std::unordered_set<Transition>;
  using transitions_map = std::unordered_map<State, transitions_set>;
  FSA(const State& start_state, const states_set& states,
      const transitions_map& transitions);

  void Reset();
  void AddTransition(const State& fromState, const Transition& transition);

 private:
  State _start_state;
  State _current_state;
  states_set _states;
  transitions_map _transitions;
};

#endif