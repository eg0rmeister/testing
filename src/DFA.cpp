#include <DFA.h>

DFA::DFA(const State& start_state, const states_vec& states)
    : FSA(start_state, states) {}

bool DFA::IsFinal() const
{
  return FSA::IsFinal(_current_state.ID());
}
