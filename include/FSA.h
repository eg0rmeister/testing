// Finite-State Automaton

#ifndef COMPILER_FSA_H
#define COMPILER_FSA_H

#include <State.h>
#include <Transition.h>

#include <unordered_map>
#include <unordered_set>

class FSA {
 public:
  using transitions_set = std::unordered_set<Transition>;
  using transitions_map = std::unordered_map<State, transitions_set>;
  FSA(const transitions_map& transitions, const State& start_state);

  void Reset();
  void AddTransition(const State& fromState, Transition transition);

 private:
  State _start_state;
  State _current_state;
  std::unordered_map<State, std::unordered_set<Transition>> _transitions;
};

#endif