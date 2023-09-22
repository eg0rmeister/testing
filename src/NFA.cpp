#include <NFA.h>

NFA::NFA(const State& start_state, const states_vec& states,
         const transitions_map& transitions)
    : FSA(start_state, states) {}
