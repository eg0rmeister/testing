#include <NFA.h>

NFA::NFA(const State& start_state, const states_vec& states)
    : FSA(start_state, states) {}
