#include <NFA.h>

#include <queue>
#include <iostream>

NFA::NFA(const State& start_state, const states_vec& states)
    : FSA(start_state, states) {}

void NFA::AddEpsilonTransition(uint32_t from_id, uint32_t to_id) {
  AddTransition(from_id, to_id, "~");
}

FSA::transitions_set NFA::GetTransitionsByLetter(const State& state,
                                                 std::string letter) const {
  auto transitions = GetTransitions(state);
  FSA::transitions_set filtered_transitions;
  for (const auto& transition : transitions) {
    if (transition.Input() == letter) {
      filtered_transitions.push_back(transition);
    }
  }
  return filtered_transitions;
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
  ret.AddTransition(ret.GetStartState().ID(), Transition(nfa.GetStartState()));
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

bool GetTransitions(
    const NFA& nfa, const State& state,
    std::unordered_map<State, std::vector<Transition>>& dp_transitions,
    std::unordered_map<State, bool>& dp_final) {
  if (dp_transitions.contains(state)) {
    return dp_final.at(state);
  }
  dp_transitions[state] = std::vector<Transition>();
  if (!dp_final.contains(state)) {
    dp_final[state] = false;
  }
  for (auto transition : nfa.GetTransitions(state)) {
    if (transition.Input() != "~") {
      dp_transitions[state].push_back(
          Transition(transition.Input(), transition.Target()));
      continue;
    }
    dp_final[state] =
        GetTransitions(nfa, transition.Target(), dp_transitions, dp_final) ||
        dp_final.at(state);
    for (auto epath : dp_transitions[transition.Target()]) {
      dp_transitions[state].push_back(
          Transition(epath.Input(), epath.Target()));
    }
  }
  return dp_final.at(state);
}

NFA GetNFAWithNoEpsilons(const NFA& nfa) {
  FSA::states_vec states = nfa.GetStates();
  State start_state = nfa.GetStartState();
  FSA::transitions_set transtions;
  std::unordered_map<State, std::vector<Transition>> dp_transitions;
  std::unordered_map<State, bool> dp_final;
  for (auto state : nfa.GetFinalStates()) {
    dp_final[state] = true;
  }
  for (auto state : states) {
    GetTransitions(nfa, state, dp_transitions, dp_final);
  }
  std::queue<State> to_visit;
  std::unordered_set<State> visited;
  to_visit.push(start_state);
  while (!to_visit.empty()) {
    State current = to_visit.front();
    to_visit.pop();
    if (visited.contains(current)) {
      continue;
    }
    visited.insert(current);
    for (auto transition : dp_transitions.at(current)) {
      to_visit.push(transition.Target());
    }
  }
  states.clear();
  for (auto state : visited) {
    states.push_back(state);
  }
  NFA ret(start_state, states);
  for (auto transitions : dp_transitions) {
    if (visited.contains(transitions.first)) {
      for (auto transition : transitions.second) {
        ret.AddTransition(transitions.first.ID(), transition);
      }
    }
  }
  for (auto state : states) {
    ret.SetFinal(state.ID(), dp_final[state]);
  }
  return ret;
}
