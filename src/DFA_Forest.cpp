#include <DFA_Forest.h>

DFAForest::DFAForest(std::vector<DFA> automatons) : _automatons(automatons) {}

bool DFAForest::Input(std::string input) {
  bool is_final = false;
  for (auto& dfa : _automatons) {
    is_final = dfa.Input(input) || is_final;
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

void DFAForest::ResetState() {
  for (auto& dfa : _automatons) {
    dfa.ResetState();
  }
}
