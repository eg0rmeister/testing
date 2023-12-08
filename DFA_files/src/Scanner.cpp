#include "Scanner.h"

Scanner::Scanner(DFAForest forest) : _forest(forest) {}

Scanner::Scanner(DFAForest forest, std::vector<size_t> tokens)
    : _forest(forest), _dfa_tokens(tokens) {}

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
  _forest.ResetState();
}

uint32_t Scanner::GetLastTerminalId() const { return _last_terminal; }

std::string Scanner::GetLastTerminalString() const {
  return _last_terminal_lexem;
}

Token Scanner::GetLastToken() const {
  size_t dfa_id = _last_terminal;
  if (dfa_id >= _dfa_tokens.size()) {
    return Token(_last_terminal_lexem, ERROR);
  }
  return Token(_last_terminal_lexem, _dfa_tokens[dfa_id]);
}

std::string Scanner::GetCurrentString() const { return _current_lexem; }
