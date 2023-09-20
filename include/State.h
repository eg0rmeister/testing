#ifndef COMPILER_STATE_H
#define COMPILER_STATE_H

#include <string>

class State {
 public:
  State(const std::string& label, bool is_final, const std::string& type = "common");
  bool IsFinal();
  std::string Label();
  std::string Type();

 private:
  std::string _label;
  std::string
      _type;  // 'common' - for non-final, other - for different final states
  bool _is_final;
};

#endif