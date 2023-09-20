#include "State.h"

State::State(const std::string& label, bool is_final, uint8_t type)
    : _label(label), _is_final(is_final), _type(type) {}

bool State::IsFinal() const { return this->_is_final; }

std::string State::Label() const { return this->_label; }

uint8_t State::Type() const { return this->_type; }