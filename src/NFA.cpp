#include <NFA.h>

NFA::NFA(const State& start_state, const states_vec& states)
    : FSA(start_state, states) {}

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
                    Transition("", ret.GetState(rhs.GetStartState().ID())));
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
  State start_state = State("", false);
  State end_state = State("", true);
  states.push_back(start_state);
  states.push_back(end_state);
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
  
  ret.AddTransition(start_state.ID(), lhs.GetStartState().ID(), "");
  ret.AddTransition(start_state.ID(), rhs.GetStartState().ID(), "");
  
  ret.AddTransition(lhs.GetStartState().ID(), start_state.ID(), "");
  ret.AddTransition(rhs.GetStartState().ID(), start_state.ID(), "");
  return ret;
}

NFA IterateNFA(const NFA& nfa) {
  FSA::states_vec states(nfa.GetStates());
  states.push_back(State("", true));
  NFA ret(states.back(), states);
  for (auto transitions_source : nfa.GetAllTransitions()) {
    for (auto transition : transitions_source.second) {
      ret.AddTransition(transitions_source.first, transition);
    }
  }
  ret.SetFinal(nfa.GetFinalStates()[0].ID(), true);
  ret.AddTransition(ret.GetFinalStates()[0].ID(),
                    Transition("", ret.GetState(ret.GetStartState().ID())));
  return ret;
}

NFA BuildEmptyNFA() {
  auto start_state = State("s", false);
  auto end_state = State("f", true);
  std::vector<State> states({start_state, end_state});
  auto nfa = NFA(start_state, states);
  nfa.SetFinal(end_state.ID());
  return nfa;
}

NFA BuildEpsNFA() {
  auto start_state = State("s", false);
  std::vector<State> states({start_state});
  auto nfa = NFA(start_state, states);
  nfa.SetFinal(start_state.ID());
  return nfa;
}

NFA BuildOneLetterNFA(std::string letter) {
  auto start_state = State("s", false);
  auto end_state = State("f", true);
  std::vector<State> states({start_state, end_state});
  auto nfa = NFA(start_state, states);
  auto transition = Transition(letter, nfa.GetState(end_state.ID()));
  nfa.AddTransition(start_state.ID(), transition);
  nfa.SetFinal(end_state.ID());
  return nfa;
}
