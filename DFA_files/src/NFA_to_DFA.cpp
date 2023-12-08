#include "NFA_to_DFA.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

DFA ConvertNFAtoDFA(const NFA& nfa) {
  // Sets of NFA states are not explicitly stored in this implementation.
  // Instead we use bitmasks to save memory and be able to use hash-based structures.
  // For that purpose we enumerate all NFA states with numbers 0 ... nfa_states_count - 1.
  // We use id_mapper to get index of particular state.
  auto nfa_states = nfa.GetStates();
  size_t nfa_states_count = nfa_states.size();

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

  std::unordered_map<std::string, std::vector<Transition>> transition_by_letter;
  while (!queue.empty()) {
    current_set = queue.front().first;
    State src_state_dfa = queue.front().second;
    queue.pop();
    transition_by_letter.clear();

    // Get all outgoing transitions from states in current_set
    // and group them by letter
    for (size_t i = 0; i < nfa_states_count; ++i) {
      if (current_set[i]) {
        auto new_transitions = nfa.GetTransitions(nfa_states[i]);
        for (const auto& transition : new_transitions) {
          transition_by_letter[transition.Input()].push_back(transition);
        }
      }
    }

    // Process transitions for each letter
    for (const auto& transitions_group : transition_by_letter) {
      std::string letter = transitions_group.first;

      // Set of states reachable from current_states by this letter
      bitmask new_set(nfa_states_count, false);

      // Flag to avoig 'dead end' states
      bool is_empty = true;
      for (const auto& transition : transitions_group.second) {
        is_empty = false;
        // Add new state to set of reachable ones
        new_set[id_mapper[transition.Target().ID()]] = true;
      }

      State dest_state_dfa = mask_to_state[new_set];
      if (!is_empty) {
        dfa_transitions.push_back(
            {src_state_dfa, Transition(letter, dest_state_dfa)});

        if (!dfa_states_masks.contains(new_set)) {
          // Set of states in NFA is a new state in DFA
          dfa_states_masks.insert(new_set);
          bool is_final = false;
          // Check if there is final state among reachable ones
          for (size_t i = 0; i < nfa_states_count; ++i) {
            if (new_set[i] && nfa.IsFinal(nfa_states[i].ID())) {
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

  // Construct DFA
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