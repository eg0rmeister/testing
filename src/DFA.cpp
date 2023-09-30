#include <DFA.h>

DFA::DFA(const State& start_state, const states_vec& states)
    : FSA(start_state, states), _current_state(start_state) {}

bool DFA::Input(std::string input) {
  if (IsTrash(_current_state)) {
    return false;
  }
  FSA::transitions_set transitions = GetTransitions(_current_state);
  for (auto transition : transitions) {
    if (transition.Input() == input) {
      _current_state = transition.Target();
      return IsFinal();
    }
  }
  _current_state = GetTrash();
  return false;
}


bool DFA::IsFinal() const { return FSA::IsFinal(_current_state.ID()); }

void DFA::ResetState() { _current_state = GetStartState(); }
