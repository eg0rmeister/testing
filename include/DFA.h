// Deterministic Finite-state Automaton

#pragma once

#include <FSA.h>

class DFA : public FSA {
 public:
  DFA(const State& start_state, const states_vec& states);
};
