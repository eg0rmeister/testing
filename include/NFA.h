// Non-deterministic Finite-state Automaton

#pragma once

#include <FSA.h>


class NFA : public FSA {
 public:
  NFA(const State& start_state, const states_vec& states);

 private:
};


/// @brief Merge two NFAs by connecting second to first by adding epsilon-transition from final state of first NFA to start state of second
/// @param lhs First NFA, should have exactly one final state!
/// @param rhs Second NFA, will be connected to first
/// @return Merged NFA
NFA MergeNFA(const NFA& lhs, const NFA& rhs);

/// @brief Build NFA for regexp "∅" or language ∅.
/// @return NFA that accepts ∅ (does not accept anything)
NFA BuildEmptyNFA();


/// @brief Build NFA for regexp "ε" or language {ε}.
/// @return NFA that accepts empty words (i.e. ε).
NFA BuildEpsNFA();


/// @brief Build NFA for regexp "a" or language {a} where 'a' is from alphabet
/// @param letter Letter "a" from description
/// @return NFA that accepts word "a"
NFA BuildOneLetterNFA(std::string letter);