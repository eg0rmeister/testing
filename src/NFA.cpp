#include <NFA.h>

NFA::NFA(const State& start_state, const states_vec& states)
    : FSA(start_state, states) {}

void NFA::AddEpsilonTransition(uint32_t from_id, uint32_t to_id) {
  AddTransition(from_id, to_id, "~");
}

NFA ConcatenateNFA(const NFA& lhs, const NFA& rhs) {
  NFA::states_vec states;
  NFA::states_vec left_states = lhs.GetStates();
  NFA::states_vec right_states = rhs.GetStates();
  states.reserve(left_states.size() + right_states.size());
  for (auto state : left_states) {
    states.push_back(state);
  }
  for (auto state : right_states) {
    states.push_back(state);
  }
  NFA ret(lhs.GetStartState(), states);
  for (auto transitions_source : lhs.GetAllTransitions()) {
    for (auto transition : transitions_source.second) {
      ret.AddTransition(transitions_source.first, transition);
    }
  }
  for (auto transitions_source : rhs.GetAllTransitions()) {
    for (auto transition : transitions_source.second) {
      ret.AddTransition(transitions_source.first, transition);
    }
  }
  for (auto final_state : rhs.GetFinalStates()) {
    ret.SetFinal(final_state.ID(), true);
  }
  ret.AddTransition(lhs.GetFinalStates()[0].ID(),
                    Transition(ret.GetState(rhs.GetStartState().ID())));
  return ret;
}

NFA AddNFA(const NFA& lhs, const NFA& rhs) {
  NFA::states_vec states;
  NFA::states_vec left_states = lhs.GetStates();
  NFA::states_vec right_states = rhs.GetStates();
  states.reserve(left_states.size() + right_states.size());
  for (auto state : left_states) {
    states.push_back(state);
  }
  for (auto state : right_states) {
    states.push_back(state);
  }
  State start_state = State();
  State end_state = State();
  states.push_back(start_state);
  states.push_back(end_state);
  NFA ret(start_state, states);

  for (auto transitions_source : lhs.GetAllTransitions()) {
    for (auto transition : transitions_source.second) {
      ret.AddTransition(transitions_source.first, transition);
    }
  }
  for (auto transitions_source : rhs.GetAllTransitions()) {
    for (auto transition : transitions_source.second) {
      ret.AddTransition(transitions_source.first, transition);
    }
  }

  ret.AddEpsilonTransition(start_state.ID(), lhs.GetStartState().ID());
  ret.AddEpsilonTransition(start_state.ID(), rhs.GetStartState().ID());

  ret.AddEpsilonTransition(lhs.GetFinalStates()[0].ID(), end_state.ID());
  ret.AddEpsilonTransition(rhs.GetFinalStates()[0].ID(), end_state.ID());
  ret.SetFinal(end_state.ID(), true);
  return ret;
}

NFA IterateNFA(const NFA& nfa) {
  FSA::states_vec states(nfa.GetStates());
  states.push_back(State());
  NFA ret(states.back(), states);
  for (auto transitions_source : nfa.GetAllTransitions()) {
    for (auto transition : transitions_source.second) {
      ret.AddTransition(transitions_source.first, transition);
    }
  }
  ret.SetFinal(states.back().ID(), true);
  ret.AddTransition(nfa.GetFinalStates()[0].ID(),
                    Transition(ret.GetState(ret.GetStartState().ID())));
  ret.AddTransition(ret.GetStartState().ID(),
                    Transition(nfa.GetStartState()));
  return ret;
}

NFA BuildEmptyNFA() {
  auto start_state = State();
  auto end_state = State();
  std::vector<State> states({start_state, end_state});
  auto nfa = NFA(start_state, states);
  nfa.SetFinal(end_state.ID());
  return nfa;
}

NFA BuildEpsNFA() {
  auto start_state = State();
  std::vector<State> states({start_state});
  auto nfa = NFA(start_state, states);
  nfa.SetFinal(start_state.ID());
  return nfa;
}

NFA BuildOneLetterNFA(std::string letter) {
  auto start_state = State();
  auto end_state = State();
  std::vector<State> states({start_state, end_state});
  auto nfa = NFA(start_state, states);
  auto transition = Transition(letter, nfa.GetState(end_state.ID()));
  nfa.AddTransition(start_state.ID(), transition);
  nfa.SetFinal(end_state.ID());
  return nfa;
}

FSA::transitions_set GetTransitions(const NFA& nfa, const State& state) {
  FSA::transitions_set ret;
}

NFA GetNFAWithNoEpsilons(const NFA& nfa) {
  FSA::states_vec states = nfa.GetStates();
  State start_state = nfa.GetStartState();
  FSA::transitions_set transtions;
  for (auto state : states) {
    for (auto transition : GetTransitions(nfa, state)) {
      transtions.push_back(transition);
    }
  }
}
