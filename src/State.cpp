#include "State.h"

State::State(const std::string& label, bool is_final, uint8_t type)
    : UniqueObject(), _label(label), _is_final(is_final), _type(type) {}

bool State::IsFinal() const { return this->_is_final; }

std::string State::Label() const { return this->_label; }

uint8_t State::Type() const { return this->_type; }

bool operator==(const State& lhs, const State& rhs) {
  return lhs.ID() == rhs.ID();
}

// Instantiate Hash for State to store State objects in unordered sets and maps

std::size_t std::hash<State>::operator()(const State& state) const {
  // Use unique state ID
  return state.ID();
}
