#include "State.h"

State::State(const std::string& label, bool is_final,
             const std::string& type)
    : _label(label), _is_final(is_final), _type(type) {}

bool State::IsFinal() { return this->_is_final; }

std::string State::Label() { return this->_label; }

std::string State::Type() { return this->_type; }