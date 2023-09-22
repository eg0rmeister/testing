// Non-deterministic Finite-state Automaton

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H

#include <FSA.h>


class NFA : public FSA {
 public:
  NFA(const State& start_state, const states_vec& states);

 private:
};

NFA MergeNFA(const NFA& lhs, const NFA& rhs);

#endif