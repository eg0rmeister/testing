#pragma once

#include <DFA.h>
#include <vector>

class DFAForest {
  public:

  /// @brief Creates a set of DFAs
  /// @param automatons DFAs to make forest of
  DFAForest(std::vector<DFA> automatons);

  /// @brief Shift every DFA according to letter
  /// @param input Letter to shift by
  /// @return Whether any of automatons arrived to a final state
  bool Input(std::string input);
  
  /// @brief Check if any of automatons is in a final state
  /// @return true if any of automatons is in a final state
  bool IsFinal();

  /// @brief Check which automatons are in a final state
  /// @return vector of indexes of automatons that are in a final state
  std::vector<uint32_t> WhichFinal();

  /// @brief Resets the state of all automatons to start state
  void ResetState();
  private:
  std::vector<DFA> _automatons;


};
