#ifndef COMPILER_STATE_H
#define COMPILER_STATE_H

#include <string>

enum { IDENT, LPARENT, RPARENT, COMMON };

class State {
 public:
  State(const std::string& label, bool is_final, const uint8_t type = COMMON);
  bool IsFinal() const;
  std::string Label() const;
  uint8_t Type() const;
  uint32_t ID() const;

 private:
  std::string _label;
  uint8_t _type;  // 'common' - for non-final, other - for final states
  bool _is_final;
  uint32_t _id;
  static uint32_t _global_id;
};

bool operator==(const State& lhs, const State& rhs);

// Instantiate Hash for State to store State objects in unordered sets and maps
template <>
struct std::hash<State> {
  std::size_t operator()(const State& state) const;
};

#endif