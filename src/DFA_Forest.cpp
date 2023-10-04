#include <DFA_Forest.h>

DFAForest::DFAForest(std::vector<DFA> automatons) : _automatons(automatons) {}

bool DFAForest::Input(std::string input) {
  bool is_final = false;
  for (auto& dfa : _automatons) {
    is_final = dfa.Input(input) || is_final;
  }
  return is_final;
}

bool DFAForest::TestWord(std::string word, bool from_current_state) {
  bool is_final = false;
  for (auto& dfa : _automatons) {
    is_final = dfa.TestWord(word) || is_final;
  }
  return is_final;
}

bool DFAForest::IsFinal() {
  for (const auto& dfa : _automatons) {
    if (dfa.IsFinal()) {
      return true;
    }
  }
  return false;
}

std::vector<uint32_t> DFAForest::WhichFinal() {
  std::vector<uint32_t> ret;
  for (uint32_t i = 0; i < _automatons.size(); ++i) {
    if (_automatons[i].IsFinal()) {
      ret.push_back(i);
    }
  }
  return ret;
}

bool DFAForest::IsError() const {
  for (const auto& automaton : _automatons) {
    if (!automaton.IsInTrash()) {
      return false;
    }
  }
  return true; 
}

void DFAForest::ResetState() {
  for (auto& dfa : _automatons) {
    dfa.ResetState();
  }
}
