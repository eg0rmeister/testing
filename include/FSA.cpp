#include "FSA.h"

FSA::FSA(const transitions_map& transitions, const State& start_state)
    : _transitions(transitions),
      _start_state(start_state),
      _current_state(start_state) {}

void FSA::Reset() { _current_state = _start_state; }

void FSA::AddTransition(const State& fromState, Transition transition) {
  _transitions[fromState].insert(transition);
}
