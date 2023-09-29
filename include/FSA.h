// Finite-State Automaton

#pragma once

#include <State.h>
#include <Transition.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>

class FSA {
 public:
  using state_ptr = State*;
  using states_vec = std::vector<State>;
  using states_set = std::vector<state_ptr>;
  using states_map = std::unordered_map<uint32_t, state_ptr>;
  using final_states_map = std::unordered_map<uint32_t, bool>;
  using transitions_set = std::vector<Transition>;
  using transitions_map = std::unordered_map<uint32_t, transitions_set>;

  /// @brief FSA constructor. States in automaton will have same IDs as provided ones
  /// @param start_state Start state of automaton
  /// @param states Vector of all states of automaton including start_state
  FSA(const State& start_state, const states_vec& states);
  ~FSA();

  void Reset();

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
  state_ptr GetState(uint32_t state_id);

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
  transitions_set GetTransitions(const State& state);


  /// @brief Mark state as final or non-final
  /// @param state_id ID of the state
  /// @param is_final True if state should be final
  void SetFinal(uint32_t state_id, bool is_final = true);


  /// @brief Print all states and transitions
  void Visualize();

 private:
  state_ptr _start_state;
  state_ptr _current_state;
  state_ptr _trash;
  states_set _states;
  states_map _state_by_id;
  final_states_map _is_final_state;
  transitions_map _transitions;
};