#include <Transition.h>

uint32_t Transition::_global_id = 0;

Transition::Transition() : _id(++_global_id) {}

uint32_t Transition::ID() const { return this->_id; }

bool operator==(const Transition& lhs, const Transition& rhs) {
  return lhs.ID() == rhs.ID();
}

// Instantiate Hash for State to store State objects in unordered sets and maps

std::size_t std::hash<Transition>::operator()(const Transition& transition) const {
  // Use unique transition ID
  return transition.ID();
}
