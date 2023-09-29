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
NFA ConcatenateNFA(const NFA& lhs, const NFA& rhs);

/// @brief Merge two NFAs by connecting them parallel to each other
/// @param lhs First NFA, should have exactly one final state!
/// @param rhs Second NFA, should have exactly one final state too!
/// @return Merged NFA
NFA AddNFA(const NFA& lhs, const NFA& rhs);

/// @brief Create a new NFA that accepts iterations of words accepted by given NFA
/// @param nfa NFA, should have exactly one final state!
/// @return Merged NFA
NFA IterateNFA(const NFA& nfa);

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


/// @brief collapses epsilon-paths
/// @param nfa 
/// @return 
NFA GetNFAWithNoEpsilons(const NFA& nfa);