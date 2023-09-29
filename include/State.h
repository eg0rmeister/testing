#pragma once

#include <UniqueObject.h>

#include <string>

enum { IDENT, TRASH, LPARENT, RPARENT, COMMON };

class State : public UniqueObject {
 public:
  State();
};

bool operator==(const State& lhs, const State& rhs);

// Instantiate Hash for State to store State objects in unordered sets and maps
template <>
struct std::hash<State> {
  std::size_t operator()(const State& state) const;
};