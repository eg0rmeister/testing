#include "FSA.h"

#include <iostream>

FSA::FSA(const State& start_state, const states_vec& states)
    : _start_state(new State(start_state)),
      _current_state(new State(start_state)),
      _trash(new State("T")) {
  for (auto& state : states) {
    _states.push_back(new State(state));
    _state_by_id[state.ID()] = *_states.rbegin();
    _is_final_state[state.ID()] = false;
  }
}

FSA::~FSA() {
  for (auto state_ptr : _states) {
    delete state_ptr;
  }
  delete _start_state;
  delete _current_state;
  delete _trash;
}

void FSA::Reset() { _current_state = _start_state; }

void FSA::AddTransition(uint32_t from_id, const Transition& transition) {
  _transitions[from_id].push_back(transition);
}

void FSA::AddTransition(uint32_t from_id, uint32_t to_id,
                        const std::string& input) {
  Transition transition = Transition(input, GetState(to_id));
  _transitions[from_id].push_back(transition);
}

FSA::transitions_map FSA::GetAllTransitions() const { return _transitions; }

void FSA::AddState(const State& state, bool is_final) {
  if (_state_by_id.contains(state.ID())) {
    _is_final_state[state.ID()] = is_final;
    return;
  }

  _states.push_back(new State(state));
  _state_by_id[state.ID()] = _states.back();
  _is_final_state[state.ID()] = is_final;
}

FSA::state_ptr FSA::GetState(uint32_t state_id) {
  return _state_by_id[state_id];
}

State FSA::GetStartState() const { return *_start_state; }

FSA::states_vec FSA::GetStates() const {
  states_vec ret;
  ret.reserve(_states.size());
  for (auto state_pointer : _states) {
    ret.push_back(*state_pointer);
  }
  return ret;
}

std::vector<State> FSA::GetFinalStates() const {
  std::vector<State> final_states;
  for (auto state : _states) {
    if (_is_final_state.contains(state->ID()) &&
        _is_final_state.at(state->ID())) {
      final_states.emplace_back(*state);
    }
  }
  return final_states;
}

FSA::transitions_set FSA::GetTransitions(const State& state) const {
  return _transitions.at(state.ID());
}

void FSA::SetFinal(uint32_t state_id, bool is_final) {
  if (_is_final_state.contains(state_id)) {
    _is_final_state[state_id] = is_final;
  }
}

void FSA::Visualize() {
  std::cout << "States: " << std::endl;
  for (auto state : _states) {
    std::cout << "[" << state->ID() << "] " << state->Label() << std::endl;
  }

  std::cout << "Transitions: " << std::endl;
  for (auto state : _states) {
    if (_transitions.contains(state->ID())) {
      auto& current_transitions = _transitions.at(state->ID());

      for (const Transition& current_transition : current_transitions) {
        std::cout << state->Label() << " - " << current_transition.Input()
                  << " -> " << current_transition.Target()->Label()
                  << std::endl;
      }
    }
  }
}
