#pragma once

#include <UniqueObject.h>

#include <string>

enum { IDENT, TRASH, LPARENT, RPARENT, COMMON };

class State : public UniqueObject {
 public:
  State();
  State(const std::string& label);
  std::string Label() const;

  /// @brief Change name of state
  /// @param new_label New name of state
  void SetLabel(const std::string& new_label);
 private:
  std::string _label;
};

bool operator==(const State& lhs, const State& rhs);

// Instantiate Hash for State to store State objects in unordered sets and maps
template <>
struct std::hash<State> {
  std::size_t operator()(const State& state) const;
};