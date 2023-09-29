#include "State.h"

State::State() : UniqueObject() {}

bool operator==(const State& lhs, const State& rhs) {
  return lhs.ID() == rhs.ID();
}

// Instantiate Hash for State to store State objects in unordered sets and maps

std::size_t std::hash<State>::operator()(const State& state) const {
  // Use unique state ID
  return state.ID();
}
