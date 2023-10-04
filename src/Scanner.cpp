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
