#ifndef COMPILER_STATE_H
#define COMPILER_STATE_H

#include <string>

enum{
  IDENT,
  LPARENT,
  RPARENT,
  COMMON
};

class State {
 public:
  State(const std::string& label, bool is_final,
        const uint8_t type = COMMON);
  bool IsFinal() const;
  std::string Label() const;
  uint8_t Type() const;

 private:
  std::string _label;
  uint8_t _type;  // 'common' - for non-final, other - for final states
  bool _is_final;
};

#endif