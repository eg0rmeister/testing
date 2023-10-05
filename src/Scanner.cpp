#include "Scanner.h"

Scanner::Scanner(DFAForest forest) : _forest(forest) {}

bool Scanner::Input(std::string input) {
  _current_lexem += input;
  if (_forest.Input(input)) {
    _last_terminal = _forest.WhichFinal()[0];
    _last_terminal_lexem = _current_lexem;
  }
  return _forest.IsError();
}

void Scanner::Reset() {
  _current_lexem = "";
  _last_terminal = _forest.GetSize();
  _last_terminal_lexem = "";
}

uint32_t Scanner::GetLastTerminalId() const { return _last_terminal; }

std::string Scanner::GetLastTerminalString() const {
  return _last_terminal_lexem;
}

std::string Scanner::GetCurrentString() const { return _current_lexem; }
