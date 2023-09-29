#include "State.h"

State::State()
    : UniqueObject(), _label(std::to_string(this->ID())) {}

State::State(const std::string& label)
    : UniqueObject(), _label(label) {}

std::string State::Label() const { return this->_label; }

void State::SetLabel(const std::string& new_label) { _label = new_label; }

bool operator==(const State& lhs, const State& rhs) {
  return lhs.ID() == rhs.ID();
}

// Instantiate Hash for State to store State objects in unordered sets and maps

std::size_t std::hash<State>::operator()(const State& state) const {
  // Use unique state ID
  return state.ID();
}
