#pragma once
#include "DFA_Forest.h"
#include <string>

class Scanner {
 public:
  /// @brief constructor of Scanner
  /// @param forest forest
  Scanner(DFAForest forest);

  // TODO: Input and Reset should be private or protected, but for the purposes of testing they should be public
  /// @brief Scan one symbol input
  /// @param input symbol to scan
  /// @return true if the state turned to ERROR
  bool Input(std::string input);

  /// @brief Resets scanner lexem
  void Reset();

  /// @brief Gets the id of the rule that accepted the last final state
  /// @return id of the rule
  uint32_t GetLastTerminalId() const;

  /// @brief Gets the lexeme that was last accepted by any rule
  /// @return the string corresponding to the lexeme
  std::string GetLastTerminalString() const;

  /// @brief Gets the lexeme that was scanned so far
  /// @return the string corresponding to the lexeme
  std::string GetCurrentString() const;

 private:

  std::string _current_lexem = "";
  std::string _last_terminal_lexem = "";
  uint32_t _last_terminal;
};