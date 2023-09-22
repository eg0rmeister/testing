#include "FSA.h"

FSA::FSA(const State& start_state, const states_set& states,
         const transitions_map& transitions)
    : _start_state(start_state),
      _current_state(start_state),
      _states(states),
      _transitions(transitions) {}

void FSA::Reset() { _current_state = _start_state; }

void FSA::AddTransition(const State& fromState, const Transition& transition) {
  _transitions[fromState].insert(transition);
}
