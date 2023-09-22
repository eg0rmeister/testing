#include <Transition.h>

Transition::Transition() : UniqueObject() {}

bool operator==(const Transition& lhs, const Transition& rhs) {
  return lhs.ID() == rhs.ID();
}

// Instantiate Hash for State to store State objects in unordered sets and maps

std::size_t std::hash<Transition>::operator()(const Transition& transition) const {
  // Use unique transition ID
  return transition.ID();
}
