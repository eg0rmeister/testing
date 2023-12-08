// Finite-State Automaton

#pragma once

#include <State.h>
#include <Transition.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>

class FSA {
 public:
  using states_vec = std::vector<State>;
  using states_set = std::vector<State>;
  using states_map = std::unordered_map<uint32_t, State>;
  using final_states_map = std::unordered_map<uint32_t, bool>;
  using transitions_set = std::vector<Transition>;
  using transitions_map = std::unordered_map<uint32_t, transitions_set>;

  /// @brief FSA constructor. States in automaton will have same IDs as provided ones
  /// @param start_state Start state of automaton
  /// @param states Vector of all states of automaton including start_state
  FSA(const State& start_state, const states_vec& states);

  /// @brief Add new transition to automaton
  /// @param from_id ID of source state
  /// @param transition 
  void AddTransition(uint32_t from_id, const Transition& transition);

  /// @brief Add new transition to automaton
  /// @param from_id ID of source state
  /// @param to_id ID of destination state
  /// @param input letter of the transition
  void AddTransition(uint32_t from_id, uint32_t to_id, const std::string& input);

  /// @brief Get all the transitions of the automaton
  /// @return unordered map of transitions (State ID -> transitions_set)
  transitions_map GetAllTransitions() const;

  /// @brief Add new state to automaton
  /// @param state State to be added
  /// @param is_final True if added state is supposed to be final
  void AddState(const State& state, bool is_final = false);

  /// @brief Get pointer to state by ID
  /// @param state_id ID of requested state
  /// @return Pointer to requested state - State*
  State GetState(uint32_t state_id);

  /// @brief Get start state
  /// @return Start state copy
  State GetStartState() const;

  /// @brief Get all states a FSA has
  /// @return vector of copies of states
  states_vec GetStates() const;


  /// @brief Get all states marked as final in the automaton
  /// @return Vector of all final states
  std::vector<State> GetFinalStates() const;


  /// @brief Gives vector of all transitions from selected state
  /// @param state State from which to give transitions
  /// @return std::vector<State> of all transitions from selected state
  transitions_set GetTransitions(const State& state) const;


  /// @brief Mark state as final or non-final
  /// @param state_id ID of the state
  /// @param is_final True if state should be final
  void SetFinal(uint32_t state_id, bool is_final = true);

  /// @brief Check if state is final
  /// @param state_id ID of state
  /// @return true if this state is final 
  bool IsFinal(uint32_t state_id) const;

  /// @brief Print all states and transitions
  void Visualize();


  /// @brief Returns state label
  /// @param state State, whose label is to be returned
  /// @return std::string state label
  std::string GetLabel(const State& state) const;

  /// @brief returns whether given state is automaton's trash
  /// @param state State to check
  /// @return true if state is trash
  bool IsTrash(const State& state) const;

  /// @brief Gives trash state
  /// @return Copy of trash state
  State GetTrash() const;

 private:
  State _start_state;
  State _trash;
  states_set _states;
  states_map _state_by_id;
  final_states_map _is_final_state;
  transitions_map _transitions;
};