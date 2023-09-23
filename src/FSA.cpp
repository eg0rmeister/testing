#include "FSA.h"

FSA::FSA(const State& start_state, const states_vec& states)
    : _start_state(new State(start_state)),
      _current_state(new State(start_state)),
      _trash(new State("T", true, TRASH)) {
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

FSA::state_ptr FSA::GetState(uint32_t state_id) {
  return _state_by_id[state_id];
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

void FSA::SetFinal(uint32_t state_id, bool is_final) {
  if (_is_final_state.contains(state_id)) {
    _is_final_state[state_id] = is_final;
  }
}
