// Finite-State Automaton

#ifndef COMPILER_FSA_H
#define COMPILER_FSA_H

#include <State.h>
#include <Transition.h>
#include <unordered_map>
#include <unordered_set>

class FSA {
  // Base class for NFA and DFA
 public:
  void Reset();
  void AddTransition(const State &fromState, Transition transition);

 private:
  State _start_state;
  State _current_state;
  std::unordered_map<State, std::unordered_set<Transition>> _transitions;
};

#endif