#include "StackMemory.h"

#include <iostream>

void StackMemory::Declare(const std::string& name, Printable value) {
  if (CheckDeclared(name)) {
    throw(std::runtime_error("Variable " + name +
                             " already declared in this scope"));
  }
  _declare_history.push_back(name);
  _variables_history[name].push(value);
}

void StackMemory::Set(const std::string& name, Printable value) {
  if (!CheckDeclared(name)) {
    throw(std::runtime_error("Variable " + name +
                             " was not declared in this scope"));
  }
  _variables_history[name].pop();
  _variables_history[name].push(value);
}

void StackMemory::SetOrDeclare(const std::string& name, Printable value) {
  if (!CheckDeclared(name)) {
    Declare(name, value);
  } else {
    Set(name, value);
  }
}

Printable StackMemory::Get(const std::string& name) {
  if (!CheckDeclared(name)) {
    throw(std::runtime_error("Variable " + name +
                             " was not declared in this scope"));
  }
  return _variables_history.at(name).top();
}

void StackMemory::Scope_in() { _declare_history.push_back(_declare_delimiter); }

void StackMemory::Scope_out() {
  std::string current_name = _declare_history.back();
  _declare_history.pop_back();
  while (current_name != _declare_delimiter) {
    _variables_history.at(current_name).pop();
    current_name = _declare_history.back();
    _declare_history.pop_back();
  }
}

bool StackMemory::CheckDeclared(const std::string& name) {
  size_t distance_from_end = 1;
  while (distance_from_end <= _declare_history.size()) {
    if (_declare_history[_declare_history.size() - distance_from_end] ==
        _declare_delimiter) {
      break;
    }
    if (_declare_history[_declare_history.size() - distance_from_end] == name) {
      return true;
    }
    ++distance_from_end;
  }
  return false;
}