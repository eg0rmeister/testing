#include <NFA.h>

NFA::NFA(const State& start_state, const states_vec& states)
    : FSA(start_state, states) {}

NFA BuildEmptyNFA()
{
  auto start_state = State("s", false);
  auto end_state = State("f", true);
  std::vector<State>states({start_state, end_state});
  auto nfa = NFA(start_state, states);
  nfa.SetFinal(end_state.ID());
  return nfa;
}

NFA BuildEpsNFA()
{
  auto start_state = State("s", false);
  std::vector<State>states({start_state});
  auto nfa = NFA(start_state, states);
  nfa.SetFinal(start_state.ID());
  return nfa;
}

NFA BuildOneLetterNFA(std::string letter)
{
  auto start_state = State("s", false);
  auto end_state = State("f", true);
  std::vector<State>states({start_state, end_state});
  auto nfa = NFA(start_state, states);
  auto transition = Transition(letter, nfa.GetState(end_state.ID()));
  nfa.AddTransition(start_state.ID(), transition);
  nfa.SetFinal(end_state.ID());
  return nfa;
}
