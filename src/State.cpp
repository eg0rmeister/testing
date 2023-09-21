#include "State.h"

uint32_t State::_global_id = 0;

State::State(const std::string& label, bool is_final, uint8_t type)
    : _label(label), _is_final(is_final), _type(type), _id(++_global_id) {}

bool State::IsFinal() const { return this->_is_final; }

std::string State::Label() const { return this->_label; }

uint8_t State::Type() const { return this->_type; }

uint32_t State::ID() const { return this->_id; }

bool operator==(const State& lhs, const State& rhs) {
  return lhs.ID() == rhs.ID();
}

// Instantiate Hash for State to store State objects in unordered sets and maps

std::size_t std::hash<State>::operator()(const State& state) const {
  // Use unique state ID
  return state.ID();
}
