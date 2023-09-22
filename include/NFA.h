// Non-deterministic Finite-state Automaton

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H

#include <FSA.h>
#include <vector>

class NFA : public FSA {
 public:
  NFA(const transitions_map& transitions, const State& start_state);

  void SetStartState(const State& new_start_state);

  std::vector<State> GetFinalStates();

  State& GetState(const State& state);

  void MakeFinal(const State& state);

  void MakeNonFinal(const State& state);

 private:
};

NFA MergeNFA(const NFA& lhs, const NFA& rhs);

#endif