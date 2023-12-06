// Deterministic Finite-state Automaton

#pragma once

#include <FSA.h>

class DFA : public FSA {
 public:
  DFA(const State& start_state, const states_vec& states);

  /// @brief Moves the state of the automaton according to the given letter
  /// @param input Letter to move by
  /// @return Whether the resulting state is final
  bool Input(std::string input);

  /// @brief Checks if DFA accepts given word. After reading word automaton remains in last state
  /// @param word Word to check, each character is interpreted as a letter
  /// @param from_current_state If true, automaton starts from current state. Otherwise it resets
  /// @return True if automaton reached final state after reading word
  bool TestWord(std::string word, bool from_current_state = false);

  /// @brief Checks whether the DFA is in final state
  /// @return true if the DFA is in final state
  bool IsFinal() const;


  /// @brief Returns automaton to starting state
  void ResetState();
private:
  State _current_state;
};
