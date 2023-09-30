#include <NFA_to_DFA.h>

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

DFA ConvertNFAtoDFA(NFA nfa) {
  auto nfa_states = nfa.GetStates();
  size_t nfa_states_count = nfa_states.size();
  char alphabet[] = {'a', 'b', 'c', 'd'};

  using bitmask = std::vector<bool>;
  using triple = std::pair<State, Transition>;

  // maps state ID to index in nfa_states array
  std::unordered_map<size_t, size_t> id_mapper;
  for (size_t i = 0; i < nfa_states.size(); ++i) {
    id_mapper[nfa_states[i].ID()] = i;
  }

  std::vector<triple> dfa_transitions;
  FSA::states_set dfa_states;
  std::unordered_set<bitmask> dfa_states_masks;

  bitmask current_set(nfa_states_count);
  std::unordered_map<size_t, bool> dfa_is_final;
  State start_state = nfa.GetStartState();
  current_set[id_mapper[start_state.ID()]] = true;

  std::queue<std::pair<bitmask, State>> queue;
  queue.push({current_set, start_state});
  dfa_states.push_back(start_state);

  std::unordered_map<std::vector<bool>, State> mask_to_state;
  mask_to_state[current_set] = start_state;

  while (!queue.empty()) {
    current_set = queue.front().first;
    State src_state_dfa = queue.front().second;
    queue.pop();
    for (auto c : alphabet) {
      bitmask new_set(nfa_states_count, false);
      
      bool is_empty = true;
      for (size_t i = 0; i < nfa_states_count; ++i) {
        if (current_set[i]) {
          auto new_transitions =
              nfa.GetTransitionsByLetter(nfa_states[i], std::string(1, c));
          for (auto& transition : new_transitions) {
            is_empty = false;
            new_set[id_mapper[transition.Target().ID()]] = true;
          }
        }
      }
      State dest_state_dfa = mask_to_state[new_set];
      if (!is_empty) {
        dfa_transitions.push_back(
            {src_state_dfa, Transition(std::string(1, c), dest_state_dfa)});

        if (!dfa_states_masks.contains(new_set)) {
          dfa_states_masks.insert(new_set);
          bool is_final = false;
          for (const auto& state_idx : new_set) {
            if (state_idx == true && nfa.IsFinal(nfa_states[state_idx].ID())) {
              is_final = true;
              break;
            }
          }
          dfa_states.push_back(dest_state_dfa);
          queue.push({new_set, dest_state_dfa});
          if (is_final) {
            dfa_is_final[dest_state_dfa.ID()] = true;
          }
        }
      }
    }
  }
  DFA dfa(dfa_states[0], dfa_states);
  for (const auto& transition : dfa_transitions) {
    dfa.AddTransition(transition.first.ID(), transition.second);
  }
  for (const auto& state : dfa_states) {
    if (dfa_is_final[state.ID()]) {
      dfa.SetFinal(state.ID());
    }
  }
  return dfa;
}
